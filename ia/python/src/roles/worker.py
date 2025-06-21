##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## worker.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action
from src.stones import STONES

class Worker(BaseRole):
    def __init__(self):
        super().__init__()
        self.mode = 'GATHERING' # GATHERING or DELIVERING
        self.carry = None
        self.pos = (0, 0)
        self.queens_pos = (0, -3)
        
    def decide_action(self):
        # if self.state.motivation.hunger > 0.7:
            # logique pour chercher de la food (vision...)
        
        if self.mode == 'GATHERING':
            coords = self.state.level
            for index, objects in enumerate(self.state.vision):
                for stone in STONES:
                    if stone in objects:
                        self.carry = stone
                        self.mode = 'DELIVERING'
                        self.queue.appendleft(Commands(Action.TAKE, stone))
                    # return logique d'exploration
            # return logique d'exploration
            
        if self.mode == 'DELIVERING':
            if self.pos == self.queens_pos:
               self.mode = 'GATHERING'
               self.queue.appendleft(Commands(Action.SET, self.carry))
               self.carry = None
            # logique pour aller jusqu'au queens

    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False