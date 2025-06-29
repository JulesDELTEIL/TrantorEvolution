##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## worker.py
##

import random

from src.roles.base_role import BaseRole
from src.action import Commands, Action
from src.macros import STONES, X, Y
from src.utils import get_movements

class Worker(BaseRole):
    def __init__(self):
        super().__init__()
        self.mode = 'GATHERING' # GATHERING or DELIVERING
        self.carry = None
        self.queens_pos = [0, 0]
        self._direction = "up"
        self.check_eat = True
        self.random = random
        
    def decide_action(self) -> None:
        self._cycle += 1
        if self.mode == 'GATHERING':
            if self.carry is not None:
                return
            if self.pos[X] == self.queens_pos[X] and self.pos[Y] == self.queens_pos[Y]:
                self._queue.appendleft(Commands(Action.FORWARD))
                return
            if self._last_vision is not None:
                for objects in self._last_vision:
                    for stone in STONES:
                        if stone in objects:
                            self.carry = stone
                            self._queue.appendleft(Commands(Action.TAKE, stone))
                            return

            self._last_vision = None
            if self.random.choice([0,1]) == 0:
                self._queue.appendleft(Commands(Action.LEFT))
            else:
                self._queue.appendleft(Commands(Action.RIGHT))
            self._queue.appendleft(Commands(Action.FORWARD))
            self._queue.appendleft(Commands(Action.LOOK))
            self.check_eat = True
            return

        elif self.carry == None:
            self.mode = 'GATHERING'
            return
        elif self.mode == 'DELIVERING':
            if self.pos[X] == self.queens_pos[X] and self.pos[Y] == self.queens_pos[Y]:
                self.mode = 'GATHERING'
                self._queue.appendleft(Commands(Action.SET, self.carry))
                self.carry = None
                self._last_vision = None
            else:
                self._queue = get_movements(self.pos, self.queens_pos, self._direction)
    
    def setup_direction(self) -> None:
        self._queue.appendleft(Commands(Action.FORWARD))

    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False
