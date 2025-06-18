##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## queenRole.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action

class Queen(BaseRole):
    def __init__(self, *inp):
        super().__init__()
        if inp > 2 and inp[0] :
            self.give_birth = True
        else :
            self.give_birth = False

    def create_kingdom(self):
        for i in range(0, 5) :
            self.queue.appendleft(Commands(Action.FORK))
            self.queue.appendleft(Commands(Action.BROADCAST, 'queen'))
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'foreman'))
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'matriarch'))
        self.give_birth = False

    def decide_action(self):
        self.cycle += 1
        if self.give_birth:
            self.create_kingdom()
        if self.queue.empty() :
            if self._can_incant():
                self.queue.appendleft([Commands(Action.INCANTATION)])

            if self.state.inventory.get("food", 0) < 2:
                self.queue.appendleft([Commands(Action.TAKE, "food")])

            if self.cycle < 4:
                self.queue.appendleft([Commands(Action.TAKE, "food")])
            else:
                self.cycle = 0
                self.queue.appendleft([Commands(Action.LOOK)])
        
    def _can_incant(self) -> bool:
        requirements = self.state.motivation.LEVEL_REQUIREMENTS.get(self.state.level, {})
        current = self.state.vision[0].split()
        for stone, needed in requirements.items():
            if current.count(stone) < needed:
                return False
        return True
