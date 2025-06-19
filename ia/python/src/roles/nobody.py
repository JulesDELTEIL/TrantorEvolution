##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## nobody.py
##

from itertools import cycle
from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Nobody(BaseRole):
    def __init__(self):
        super().__init__()

    def decide_action(self):
        if self.queue.empty():
            self.queue.appendleft(Commands(Action.LEFT))