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
        self.foreman_direction = None
        self.pos = [0, 0]
        self.queens_pos = None
        
    def decide_action(self):
        if self.direction is None:
            if self.cycle == 0:
                self.queue.appendleft(Commands(Action.FORWARD))
                self.cycle += 1
            return
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
    
    def setup_direction(self) -> None:
        self.queue.appendleft(Commands(Action.FORWARD))

    def handle_broadcast(self, response_list: list[str]) -> bool:
        if self.direction is None:
            if response_list[1][0] == "2":
                self.queue.appendleft(Commands(Action.LEFT))
                self.queue.appendleft(Commands(Action.LEFT))
                self.queens_pos = [0, -2]
            if response_list[1][0] == "4":
                self.queue.appendleft(Commands(Action.RIGHT))
                self.queens_pos = [1, -3]
            if response_list[1][0] == "8":
                self.queue.appendleft(Commands(Action.LEFT))
                self.queens_pos = [-1, -3]
                
            self.direction = "up"
            
        return False