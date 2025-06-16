##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## worker.py
##

from ia.roles.base_role import BaseRole
from action import Commands, Action
from stones import STONES

class Worker(BaseRole):
    def __init__(self):
        super().__init__()
        self.mode = 'GATHERING' # GATHERING or DELIVERING
        self.carry = None
        self.pos = (0, 0)
        self.queens_pos = (0, -3)
        
    def decide_action(self) -> list[Commands]:
        commands_queue = []
        # if self.state.motivation.hunger > 0.7:
            # logique pour chercher de la food (vision...)
        
        if self.mode == 'GATHERING':
            coords = self.state.level
            for index, objects in enumerate(self.state.vision):
                for stone in STONES:
                    if stone in objects:
                        self.carry = stone
                        self.mode = 'DELIVERING'
                        commands_queue.append(Commands(Action.TAKE, stone))
                        return commands_queue
                    # return logique d'exploration
            # return logique d'exploration
            
        if self.mode == 'DELIVERING':
            if self.pos == self.queens_pos:
               self.mode = 'GATHERING'
               commands_queue.append(Commands(Action.SET, self.carry))
               self.carry = None
               return commands_queue
            # logique pour aller jusqu'au queens
        