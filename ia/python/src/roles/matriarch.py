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
        print("----- Je suis Matriarch ------")
    
    def decide_action(self):
        commands_queue = []
        self.cycle += 1

        if self.cycle % 4 == 0:
            self.queue.appendleft(Commands(Action.TAKE, 'food'))


        self.queue.appendleft(Commands(Action.FORK))
        
        # à faire -> Connecter nouveau client
        
        self._fork_count += 1
        self.queue.appendleft(Commands(Action.BROADCAST, 'role kamikaze'))
        
    def handle_broadcast(self, response_list: list[str]) -> bool:
        return False
