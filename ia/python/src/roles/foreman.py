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
    
    def decide_action(self) -> list[Commands]:
        commands_queue = []
        self.cycle += 1
        if self._initial_moves > 0:
            self._initial_moves -= 1
            commands_queue.append(Commands(Action.FORWARD))
            return commands_queue
        
        if self.cycle % 4 == 0:
            commands_queue.append(Commands(Action.TAKE, 'food'))
            return commands_queue

        commands_queue.append(Commands(Action.FORK))
        
        # à faire -> Connecter nouveau client
        
        self._fork_count += 1
        if self._fork_count % 4 == 0:
            commands_queue.append(Commands(Action.BROADCAST, 'kamikaze'))
        else:
            commands_queue.append(Commands(Action.BROADCAST, 'worker'))
        return commands_queue
    