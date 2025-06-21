##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## irole.py
##

from abc import ABC, abstractmethod
from collections import deque
from src.player import PlayerState
from src.action import Commands
from enum import Enum

class Direction(Enum):
    UP = "up"
    DOWN = "down"
    LEFT = "left"
    RIGHT = "right"

class BaseRole(ABC):
    def __init__(self):
        self.cycle: int = 0
        self.last_sent = None
        self.direction = None
        self.queue = deque()
        self.state: PlayerState = PlayerState()
        
    @abstractmethod
    def decide_action(self) -> Commands:
        pass
