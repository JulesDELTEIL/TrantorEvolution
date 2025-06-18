##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## kamikaze.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Kamikaze(BaseRole):
    def __init__(self):
        super().__init__()
    
    def decide_action(self):
        if self.queue.empty():
            for i in range(10):
                self.queue.appendleft(Commands(Action.SET, 'food'))
        self.queue.appendleft(Commands(Action.NONE))
