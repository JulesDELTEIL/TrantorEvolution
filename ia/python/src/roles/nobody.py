##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## nobody.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Nobody(BaseRole):
    """
    When a client spawn, he'll be a Nobody.
    He wait a broadcast to know his role or become a Mother Queen if no broadcast during 10 cycle.
    """
    def __init__(self):
        super().__init__()
        self._is_there_anyone: bool = None
        self._direction: str = "up"

    def handle_broadcast(self, response_list: list[str]) -> str:
        if len(response_list) >= 3:
            if response_list[2][:4] == "role" and (response_list[1][0] == "0"):
                return "ROLE"
            if response_list[2] == "quit":
                return "QUIT"
        return "NOTHING"

    def decide_action(self) -> None:
        self._cycle += 1
        if self._cycle == 1:
            self._queue.appendleft(Commands(Action.LOOK))
        else:
            self._queue.appendleft(Commands(Action.LEFT))
