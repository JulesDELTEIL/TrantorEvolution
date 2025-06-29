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
    """
    BaseRole contains all attributes necessaries to every role.
    """
    def __init__(self):
        self._level = 1
        self._cycle: int = 0
        self._last_sent = None
        self._direction = None
        self.pos = [0, 0]
        self._queue = deque()
        self._map = MapMemory(decay=0.1)
        self._last_inventory = {}
        self._last_vision = []

    @abstractmethod
    def decide_action(self) -> Commands:
        pass
    
    @abstractmethod
    def handle_broadcast(self, response_list: list[str]) -> bool:
        pass
