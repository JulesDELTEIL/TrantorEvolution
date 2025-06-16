##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## matriarch.py
##

from ia.roles.base_role import BaseRole
from action import Commands, Action

class Matriarch(BaseRole):
    def __init__(self):
        super().__init__()
    
    def decide_action(self) -> list[Commands]:
        commands_queue = []
        self.cycle += 1

        if self.cycle % 4 == 0:
            commands_queue.append(Commands(Action.TAKE, 'food'))
            return commands_queue

        commands_queue.append(Commands(Action.FORK))
        
        # à faire -> Connecter nouveau client
        
        self._fork_count += 1
        commands_queue.append(Commands(Action.BROADCAST, 'kamikaze'))
        return commands_queue
