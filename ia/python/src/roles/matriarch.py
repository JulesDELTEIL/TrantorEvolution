##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## matriarch.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Matriarch(BaseRole):
    def __init__(self):
        super().__init__()
        self._fork_count = 0
        print("----- I'm Matriarch -----")
    
    def decide_action(self):
        self._cycle += 1

        if self._cycle % 2 == 0:
            self._queue.appendleft(Commands(Action.TAKE, 'food'))
            self._queue.appendleft(Commands(Action.TAKE, 'food'))

        self._queue.appendleft(Commands(Action.FORK))
        self._fork_count += 1
        self._queue.appendleft(Commands(Action.BROADCAST, 'role;kamikaze'))

    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False
