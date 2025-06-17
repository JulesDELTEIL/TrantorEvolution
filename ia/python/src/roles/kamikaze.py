##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## kamikaze.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Kamikaze(BaseRole):
    def __init__(self):
        super().__init__()
    
    def decide_action(self) -> list[Commands]:
        commands_queue = []
        if not commands_queue:
            for i in range(10):
                commands_queue.append(Commands(Action.SET, 'food'))
            return commands_queue

        commands_queue.append(Commands(Action.NONE))
        return commands_queue
            