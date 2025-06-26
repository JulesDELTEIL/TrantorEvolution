##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## nobody.py
##

from itertools import cycle
import socket
from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Nobody(BaseRole):
    def __init__(self):
        super().__init__()
        self._is_there_anyone = None

    def handle_broadcast(self, response_list: list[str]) -> str:
        if len(response_list) >= 3:
            if response_list[2][:4] == "role" and (response_list[1][0] == "0"):
                return "ROLE"
            if response_list[2] == "quit":
                return "QUIT"
        return "NOTHING"

    def decide_action(self):
        self.cycle += 1
        if self.cycle == 1:
            self.queue.appendleft(Commands(Action.LOOK))
        else:
            self.queue.appendleft(Commands(Action.LEFT))
