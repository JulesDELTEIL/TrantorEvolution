##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## kamikaze.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Kamikaze(BaseRole):
    """
    Kamikaze will drop all his when spawning and die.
    """
    def __init__(self):
        super().__init__()
    
    def decide_action(self) -> None:
        self._cycle += 1
        for _ in range(10):
            self._queue.appendleft(Commands(Action.SET, 'food'))
        self._queue.appendleft(Commands(Action.NONE))

    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False