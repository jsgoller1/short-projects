from enum import Enum, IntEnum


class FloorNumber(IntEnum):
    ONE = 1
    TWO = 2
    THREE = 3
    FOUR = 4
    FIVE = 5


class DoorState(Enum):
    OPEN = "open"
    CLOSED = "closed"


class MovingDirection(Enum):
    UP = "up"
    DOWN = "down"
    IDLE = "idle"
