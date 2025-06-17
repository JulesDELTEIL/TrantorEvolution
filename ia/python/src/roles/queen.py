##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## queenRole.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Queen(BaseRole):
    def __init__(self):
        super().__init__()
        
    def decide_action(self) -> list[Commands]:
        self.cycle += 1
        if self._can_incant():
            return list[Commands(Action.INCANTATION)]
        
        if self.state.inventory.get("food", 0) < 2:
            return list[Commands(Action.TAKE, "food")]
        
        if self.cycle < 4:
            return list[Commands(Action.TAKE, "food")]
        else:
            self.cycle = 0
            return list[Commands(Action.LOOK)]
        
    def _can_incant(self) -> bool:
        requirements = self.state.motivation.LEVEL_REQUIREMENTS.get(self.state.level, {})
        current = self.state.vision[0].split()
        for stone, needed in requirements.items():
            if current.count(stone) < needed:
                return False
        return True
