##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## queenRole.py
##

from action import Commands, Action
from player import PlayerState

class Queen:
    def __init__(self):
        self._cycle = 0 # 0-2: Take, 3: Look then reset to 0
        self._state = PlayerState()
        
    def decide_action(self):
        if self._can_incant():
            return Commands(Action.INCANTATION)
        
        if self._state.inventory.get("food", 0) < 2:
            return Commands(Action.TAKE, "food")
        
        if self._cycle < 3:
            return Commands(Action.TAKE, "food")
        else:
            self._cycle = 0
            return Commands(Action.LOOK)
        
    def _can_incant(self):
        requirements = self._state.motivation.LEVEL_REQUIREMENTS.get(self._state.level, {})
        current = self._state.vision[0].split()
        for stone, needed in requirements.items():
            if current.count(stone) < needed:
                return False
        return True
