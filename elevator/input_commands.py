from abc import ABC, abstractmethod
from dataclasses import dataclass
from elevator_types import FloorNumber
"""
Each command implemented by an InputDriver corresponds to a "signal"
from the physical elevator system. We assume signal transmission is perfect (no dropped or incorrect
signals).
"""


class UnknownInputCommand(Exception):
    pass


class InputCommand:
    pass


def is_valid_input_command(command: InputCommand):
    return isinstance(command, (FloorSensorTriggered, ElevatorButtonPressed, FloorButtonPressed, TimerExpired, AllYourBaseAreBelongToUs))


class AllYourBaseAreBelongToUs(InputCommand):
    # Kills everyone onboard
    pass


@dataclass
class FloorButtonPressed(InputCommand):
    # Signals a button on one of the floors was pressed
    # Must return floor and direction (up/down)
    floor_number: FloorNumber


@dataclass
class FloorSensorTriggered(InputCommand):
    # Signals the elevator is at a particular floor
    # Outputs number for which floor the elevator was detected on
    floor_number: FloorNumber


@dataclass
class ElevatorButtonPressed(InputCommand):
    # Signals a button within the elevator was pressed
    # Outputs number for which button was pressed
    floor_number: FloorNumber


class TimerExpired(InputCommand):
    # Signals a previously set timer expired
    pass
