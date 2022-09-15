"""
Probably useful to structure everything via callbacks / expectation that
whoever owns outside world and elevator production can opaquely trigger our code
and do useful things when we trigger them.

- will implement a driver class that entire system takes

"""
from collections import deque

from car import Car
from elevator_types import FloorNumber
from input_commands import is_valid_input_command, InputCommand, UnknownInputCommand
from output_commands import OutputCommand


class Elevator:
    def __init__(self):
        self._car = Car(min_floor=1, max_floor=5)
        self._input_queue = deque([])
        self._output_queue = deque([])

    def __repr__(self):
        return f"Elevator({repr(self._car)},\n {repr(self._input_queue)},\n {repr(self._output_queue)}\n)"

    def put_input_command(self, command: InputCommand):
        self._input_queue.append(command)
        self._process_input_events()

    def get_output_command(self):
        return None if len(self._output_queue) == 0 else self._output_queue.popleft()

    def _process_input_events(self):
        while len(self._input_queue):
            command = self._input_queue.popleft()
            if is_valid_input_command(command):
                output = self._car.handle_command(command)
                if isinstance(output, OutputCommand):
                    self._output_queue.append(output)
            else:
                raise UnknownInputCommand(f"Command: {command}")
