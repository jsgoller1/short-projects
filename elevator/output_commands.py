from dataclasses import dataclass
from elevator_types import MovingDirection


class OutputCommand:
    """
    Each command implemented by an OutputCommand causes a signal to be sent
    to the physical elevator system. We assume all signal transmission is perfect
    (no dropped or incorrect signals).
    """
    pass


@dataclass
class DoorMotorControl(OutputCommand):
    pass


@dataclass
class HoistMotorControl(OutputCommand):
    direction: MovingDirection


@dataclass
class SetTimer(OutputCommand):
    pass


@dataclass
class SetFloorLight(OutputCommand):
    # Nice-to-have, not in spec
    # Turns light on a floor button on or off
    pass


@dataclass
class SetButtonLight(OutputCommand):
    # Nice-to-have, not in spec
    # Turns light on an elevator button on or off
    pass
