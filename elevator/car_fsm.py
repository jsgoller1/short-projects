from abc import ABC, abstractmethod
from elevator_types import DoorState, MovingDirection
from output_commands import DoorMotorControl, HoistMotorControl, SetTimer


"""
Implements a State Pattern to manage how the elevator car should respond
to requests. Note: we are not using an explicit "FSM Manager" class that owns
state transitions; Car has an initial state that knows how to create other states
and transition to them. The states don't own any data themselves so they can be created
and thrown away willy-nilly.

The FSM represents the "doing" part of the elevator; it doesn't "know" anything, but
knows how to respond given events and what Car knows.
"""

# TODO: For now, any kind of unexpected behavior triggers an emergency stop.
# In the future, we could probably ignore some situations that aren't
# dangerous and but leave in a "paranoid mode" feature to halt on all invalid
# situations.


class CarTastropheException(Exception):
    # Yes, that is an intentional typo;
    # it's a bad pun, leave me alone
    pass


class EmergencyStop(Exception):
    # The car got input indicating something dangerous to
    # passengers; we must stop immediately.
    pass


class CarFSMState(ABC):
    def __init__(self, car):
        self.car = car

    def destroy(self):
        self.car._current_state = CarExplodedCatastrophicallyAndEveryoneDiedFSMState()
        self.car._current_state.timer_triggered()

    @abstractmethod
    def put_floor_request(self):
        raise NotImplementedError

    @abstractmethod
    def set_current_floor(self):
        raise NotImplementedError

    @abstractmethod
    def timer_triggered(self):
        raise NotImplementedError


class CarIdleFSMState(CarFSMState):
    def put_floor_request(self, floor):
        # Switch to moving state and forward request
        self.car._current_state = CarMovingFSMState(self.car)
        self.car.set_moving_direction(
            MovingDirection.UP if (floor > self.car.get_current_floor()) else MovingDirection.DOWN)
        return self.car._current_state.put_floor_request(floor)

    def set_current_floor(self):
        raise EmergencyStop("Car appears to be in motion when it is idle.")

    def timer_triggered(self):
        raise EmergencyStop(
            "Car got a timer event when it wasn't waiting for one.")


class CarMovingFSMState(CarFSMState):
    def put_floor_request(self, floor):
        self.car.request_new_floor(floor)
        return HoistMotorControl(direction=self.car.get_moving_direction())

    def set_current_floor(self, new_floor):
        # We only want to be going past floors that are one off our
        # current / last known floor in the direction we are going.
        expected_new_floor = self.car.get_current_floor() + \
            (1 if self.car.get_moving_direction() == MovingDirection.UP else -1)
        if not (new_floor == expected_new_floor):
            raise EmergencyStop(
                "Car was detected at a floor it should not be at; halting.")

        # If we got to a floor on our list of requests,
        # remove it from the list and disembark. Otherwise,
        # continue to the next floor we need to visit.
        commands = []
        self.car.set_current_floor(new_floor)
        if self.car.get_current_floor() == self.car.peek_next_floor():
            self.car.pop_next_floor()
            self.car._door_state = DoorState.OPEN
            commands.append(DoorMotorControl())
            self.car._current_state = CarLoadingFSMState(self.car)
            commands.append(SetTimer())
        else:
            commands.append(DoorMotorControl(MovingDirection.DOWN))
        return commands

    def timer_triggered(self):
        raise EmergencyStop(
            "Unexpected timer event (cannot handle timer event while car is moving).")


class CarLoadingFSMState(CarFSMState):
    def put_floor_request(self, floor):
        self.car.request_floor(floor)

    def set_current_floor(self):
        raise EmergencyStop("Car appears to be in motion while loading.")

    def timer_triggered(self):
        if self.car.door_state == DoorState.OPEN:
            # TODO: anyone in the way of the door gets smushed
            self.car.door_state = DoorState.CLOSED
            self.car._current_state = self.CarMovingFSMState(self.car)
            self.car.go_to_next_floor()
        else:
            raise EmergencyStop(
                "Got timer event when doors were closed; cannot handle this.")


class CarExplodedCatastrophicallyAndEveryoneDiedFSMState(CarFSMState):
    def __init__(self):
        self.exception_text = "The car exploded catastrophically, and everyone died. Guess you should've written more unit tests!"

    def put_floor_request(self, floor):
        raise CarTastropheException(self.exception_text)

    def set_current_floor(self, floor):
        raise CarTastropheException(self.exception_text)

    def timer_triggered(self):
        raise CarTastropheException(self.exception_text)
