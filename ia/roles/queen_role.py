##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## queenRole.py
##

from ia.roles.base_role import BaseRole
from action import Commands, Action

class Queen(BaseRole):
    def __init__(self):
        super().__init__()
        
    def decide_action(self) -> Commands:
        if self._can_incant():
            return Commands(Action.INCANTATION)
        
        if self.state.inventory.get("food", 0) < 2:
            return Commands(Action.TAKE, "food")
        
        if self.cycle < 3:
            return Commands(Action.TAKE, "food")
        else:
            self.cycle = 0
            return Commands(Action.LOOK)
        
    def _can_incant(self) -> bool:
        requirements = self.state.motivation.LEVEL_REQUIREMENTS.get(self.state.level, {})
        current = self.state.vision[0].split()
        for stone, needed in requirements.items():
            if current.count(stone) < needed:
                return False
        return True
