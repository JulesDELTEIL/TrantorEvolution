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
    """
    Walk randomly and look for stones. When he saw one, take it then bring it to kindom base.
    """
    def __init__(self):
        super().__init__()
        self.mode: str = 'GATHERING' # GATHERING or DELIVERING
        self.carry: str = None
        self.queens_pos: list[int] = [0, 0]
        self._direction: str = "up"
        self.check_eat: bool = True
        self.random = random
        
    def _is_kindom_tile(self, look_index: int) -> bool:
        if self._direction == "up":
            if look_index == 1:
                if self.pos[X] - 1 == self.queens_pos[X] and self.pos[Y] + 1 == self.queens_pos[Y]:
                    return True
            elif look_index == 2:
                if self.pos[X] == self.queens_pos[X] and self.pos[Y] + 1 == self.queens_pos[Y]:
                    return True
            elif look_index == 3:
                if self.pos[X] + 1 == self.queens_pos[X] and self.pos[Y] + 1 == self.queens_pos[Y]:
                    return True
            return False
        if self._direction == "right":
            if look_index == 1:
                if self.pos[X] + 1 == self.queens_pos[X] and self.pos[Y] + 1 == self.queens_pos[Y]:
                    return True
            elif look_index == 2:
                if self.pos[X] + 1 == self.queens_pos[X] and self.pos[Y] == self.queens_pos[Y]:
                    return True
            elif look_index == 3:
                if self.pos[X] + 1 == self.queens_pos[X] and self.pos[Y] - 1 == self.queens_pos[Y]:
                    return True
            return False
        if self._direction == "down":
            if look_index == 1:
                if self.pos[X] + 1 == self.queens_pos[X] and self.pos[Y] - 1 == self.queens_pos[Y]:
                    return True
            elif look_index == 2:
                if self.pos[X] == self.queens_pos[X] and self.pos[Y] - 1 == self.queens_pos[Y]:
                    return True
            elif look_index == 3:
                if self.pos[X] - 1 == self.queens_pos[X] and self.pos[Y] - 1 == self.queens_pos[Y]:
                    return True
            return False
        if self._direction == "left":
            if look_index == 1:
                if self.pos[X] - 1 == self.queens_pos[X] and self.pos[Y] - 1 == self.queens_pos[Y]:
                    return True
            elif look_index == 2:
                if self.pos[X] - 1 == self.queens_pos[X] and self.pos[Y] == self.queens_pos[Y]:
                    return True
            elif look_index == 3:
                if self.pos[X] - 1 == self.queens_pos[X] and self.pos[Y] + 1 == self.queens_pos[Y]:
                    return True
            return False
        
    def decide_action(self) -> None:
        self._cycle += 1
        if self.mode == 'GATHERING':
            if self.pos[X] == self.queens_pos[X] and self.pos[Y] == self.queens_pos[Y]:
                self._queue.appendleft(Commands(Action.FORWARD))
                self._last_vision = None
            if self._last_vision is not None:
                for i in range(4):
                    for objects in self._last_vision[i]:
                        if self._is_kindom_tile(i) == True:
                            continue
                        for stone in STONES:
                            if stone in objects:
                                if i == 1:
                                    self._queue.appendleft(Commands(Action.FORWARD))
                                    self._queue.appendleft(Commands(Action.LEFT))
                                    self._queue.appendleft(Commands(Action.FORWARD))
                                elif i == 2:
                                    self._queue.appendleft(Commands(Action.FORWARD))
                                elif i == 3:
                                    self._queue.appendleft(Commands(Action.FORWARD))
                                    self._queue.appendleft(Commands(Action.RIGHT))
                                    self._queue.appendleft(Commands(Action.FORWARD))
                                self.carry = stone
                                self._queue.appendleft(Commands(Action.TAKE, stone))
                                self._last_vision = None
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

        elif self.mode == 'DELIVERING':
            if self.carry is None:
                self.mode = 'GATHERING'
            if self.pos[X] == self.queens_pos[X] and self.pos[Y] == self.queens_pos[Y]:
                self._queue.appendleft(Commands(Action.SET, self.carry))
                self.carry = None
                self._last_vision = None
            else:
                self._queue = get_movements(self.pos, self.queens_pos, self._direction)
        else:
            self.mode = 'GATHERING'

    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False
