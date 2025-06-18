##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## foreman.py
##

from src.roles.base_role import *
from src.action import Commands, Action

class Foreman(BaseRole):
    def __init__(self):
        super().__init__()
        self._initial_moves = 3
        self._fork_count = 0
    
    def decide_action(self):
        self.cycle += 1
        if self._initial_moves > 0:
            self._initial_moves -= 1
            self.queue.appendleft(Commands(Action.FORWARD))

        if self.cycle % 4 == 0:
            self.queue.appendleft(Commands(Action.TAKE, 'food'))

        self.queue.appendleft(Commands(Action.FORK))

        # à faire -> Connecter nouveau client
        
        self._fork_count += 1
        if self._fork_count % 4 == 0:
            self.queue.appendleft(Commands(Action.BROADCAST, 'kamikaze'))
        else:
            self.queue.appendleft(Commands(Action.BROADCAST, 'worker'))
