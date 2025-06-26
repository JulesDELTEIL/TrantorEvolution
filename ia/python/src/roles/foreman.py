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
        print("----- Je suis Foreman ------")
        self._initial_moves = 3
        self._fork_count = 0
        self.queue.append(Commands(Action.TAKE, 'food'))
    
    def decide_action(self):
        self.cycle += 1
        if self.cycle == 1:
            self.queue.appendleft(Commands(Action.LEFT))
            return

        if self.cycle > 20:
            self.queue.appendleft(Commands(Action.TAKE, 'food'))
        if self.cycle % 2 == 0:
            self.queue.appendleft(Commands(Action.TAKE, 'food'))
            self.queue.appendleft(Commands(Action.TAKE, 'food'))

        self.queue.appendleft(Commands(Action.FORK))
        if self.cycle % 3 == 0:
            self.queue.appendleft(Commands(Action.BROADCAST, 'role;worker'))
        else:
            self.queue.appendleft(Commands(Action.BROADCAST, 'role;kamikaze'))

    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False
