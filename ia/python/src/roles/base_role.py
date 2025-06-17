##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## irole.py
##

from abc import ABC, abstractmethod
from src.player import PlayerState
from src.action import Commands

class BaseRole(ABC):
    def __init__(self):
        self.cycle: int = 0
        self.state: PlayerState = PlayerState()
        
    @abstractmethod
    def decide_action(self) -> Commands:
        pass
