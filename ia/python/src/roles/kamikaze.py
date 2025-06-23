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
        print("----- Je suis kamikaze ------")
    
    def decide_action(self):
        if self.queue.empty():
            for _ in range(10):
                self.queue.appendleft(Commands(Action.SET, 'food'))
        self.queue.appendleft(Commands(Action.NONE))
