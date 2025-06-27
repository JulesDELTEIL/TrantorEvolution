##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## worker.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action
from src.macros import STONES
from src.utils import get_movements
import random

class Worker(BaseRole):
    def __init__(self):
        super().__init__()
        print("----- Je suis Worker ------")
        self.mode = 'GATHERING' # GATHERING or DELIVERING
        self.carry = None
        self.queens_pos = [0, 0]
        self.direction = "up"
        self.random = random
        
    def decide_action(self) -> None:
        self.cycle += 1
        if self.mode == 'GATHERING':
            if self.carry is not None:
                return
            if self.pos[0] == self.queens_pos[0] and self.pos[1] == self.queens_pos[1]:
                self.queue.appendleft(Commands(Action.FORWARD))
                return
            if self.last_vision is not None:
                for objects in self.last_vision:
                    for stone in STONES:
                        if stone in objects:
                            print("je prends", stone)
                            self.carry = stone
                            self.queue.appendleft(Commands(Action.TAKE, stone))
                            return

            self.last_vision = None
            if self.random.choice([0,1]) == 0:
                self.queue.appendleft(Commands(Action.LEFT))
            else:
                self.queue.appendleft(Commands(Action.RIGHT))
            self.queue.appendleft(Commands(Action.FORWARD))
            self.queue.appendleft(Commands(Action.LOOK))
            return

        elif self.mode == 'DELIVERING':
            if self.pos[0] == self.queens_pos[0] and self.pos[1] == self.queens_pos[1]:
                print("je pose", self.carry)
                self.mode = 'GATHERING'
                self.queue.appendleft(Commands(Action.SET, self.carry))
                self.carry = None
                self.last_vision = None
            else:
                self.queue = get_movements(self.pos, self.queens_pos, self.direction)
    
    def setup_direction(self) -> None:
        self.queue.appendleft(Commands(Action.FORWARD))

    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False