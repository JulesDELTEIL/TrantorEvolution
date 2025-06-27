##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## irole.py
##

from abc import ABC, abstractmethod
from collections import deque
from src.action import Commands
from src.roles.map_memory import MapMemory

class BaseRole(ABC):
    def __init__(self):
        self.level = 1
        self.cycle: int = 0
        self.last_sent = None
        self.direction = None
        self.pos = [0, 0]
        self.queue = deque()
        self.map = MapMemory(decay=0.1)
        self.last_inventory = {}
        self.last_vision = []

    @abstractmethod
    def decide_action(self) -> Commands:
        pass
