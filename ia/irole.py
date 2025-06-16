##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## irole.py
##

from abc import ABC, abstractmethod
from player import PlayerState
from action import Commands

class IRole(ABC):
    def __init__(self):
        self.cycle: int = 0
        self.state: PlayerState = PlayerState()
        
    @abstractmethod
    def decide_action(self) -> Commands:
        pass
