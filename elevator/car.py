from car_fsm import CarIdleFSMState, CarMovingFSMState, CarLoadingFSMState
from elevator_types import FloorNumber, DoorState, MovingDirection
from input_commands import AllYourBaseAreBelongToUs, FloorButtonPressed, FloorSensorTriggered, ElevatorButtonPressed, TimerExpired, UnknownInputCommand

"""
Car doesn't "do" anything, but it "knows" and manages details about the state
of the elevator car and tells that information to the FSM. 
"""


class Car:
    def __init__(self, min_floor, max_floor, car_fsm=None, current_floor=None, door_state=None, moving_direction=None, requested_floors=None):
        self._min_floor = min_floor
        self._max_floor = max_floor
        self._current_state = car_fsm if car_fsm else CarIdleFSMState(self)
        self._current_floor = current_floor if current_floor else FloorNumber.ONE
        self._door_state = door_state if door_state else DoorState.CLOSED
        self._moving_direction = moving_direction if moving_direction else MovingDirection.IDLE
        self._requested_floors = requested_floors if requested_floors else set()

    def __repr__(self):
        return f"Car({self._min_floor},{self._max_floor},{self._current_state},{self._current_floor},{self._door_state},{self._moving_direction},{self._requested_floors},)"

    def handle_command(self, command):
        if isinstance(command, (FloorButtonPressed, ElevatorButtonPressed)):
            return self._current_state.put_floor_request(command.floor_number)
        elif isinstance(command, FloorSensorTriggered):
            return self._current_state.set_current_floor(command.floor_number)
        elif isinstance(command, TimerExpired):
            return self._current_state.timer_triggered()
        elif isinstance(command, AllYourBaseAreBelongToUs):
            return self._current_state.destroy()
        else:
            raise UnknownInputCommand(f"Command: {command}")

    def request_new_floor(self, floor):
        self._requested_floors.add(floor)

    def peek_next_floor(self):
        increments = [-1,
                      1] if self._moving_direction == MovingDirection.DOWN else [1, -1]
        for inc in increments:
            floor = self._current_floor
            while self._min_floor < floor < self._max_floor:
                if floor+inc in self._requested_floors:
                    return floor+inc
                floor += inc
        return None

    def pop_next_floor(self):
        next_floor = self.peek_next_floor()
        self._requested_floors.remove(next_floor)
        return next_floor

    def toggle_doors(self):
        self._door_state = DoorState.OPEN if self._door_state == DoorState.CLOSED else DoorState.CLOSED

    def get_moving_direction(self):
        return self._moving_direction

    def set_moving_direction(self, new_direction):
        self._moving_direction = new_direction

    def get_current_floor(self):
        return self._current_floor

    def set_current_floor(self, new_floor):
        self._current_floor = new_floor


if __name__ == '__main__':
    assert Car(1, 5, current_floor=3, requested_floors=[
               2]).get_next_floor() == 2
    assert Car(1, 5, current_floor=2, requested_floors=[
               4, 5]).get_next_floor() == 4
    assert Car(1, 5, current_floor=2).get_next_floor() == None
    assert Car(1, 5, current_floor=3, moving_direction=MovingDirection.DOWN, requested_floors=[
               2, 4, 5]).get_next_floor() == 2
    assert Car(1, 5, current_floor=3, moving_direction=MovingDirection.UP, requested_floors=[
               2, 4, 5]).get_next_floor() == 4
