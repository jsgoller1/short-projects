from elevator import Elevator
from elevator_types import FloorNumber
from input_commands import AllYourBaseAreBelongToUs, FloorButtonPressed, FloorSensorTriggered, ElevatorButtonPressed, TimerExpired

if __name__ == '__main__':
    elevator = Elevator()
    elevator.put_input_command(
        FloorButtonPressed(floor_number=FloorNumber.FIVE))
    out = elevator.get_output_command()
    print(elevator)
    print(out)
    elevator.put_input_command(AllYourBaseAreBelongToUs())
