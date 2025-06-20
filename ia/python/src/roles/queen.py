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
        if len(inp) == 1 and inp[0] :
            self.give_birth = True
        else :
            self.give_birth = False
        self.all_alone = False
        self.player_killed = 0

    def create_kingdom(self):
        for _ in range(5):
            self.queue.appendleft(Commands(Action.FORK))
            self.queue.appendleft(Commands(Action.BROADCAST, 'queen'))
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'foreman'))
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'matriarch'))
        self.give_birth = False

    def handle_mother_queen(self):
        if not self.all_alone :
            if self.player_killed >= self.state.egg_left or not self.state.egg_left:
                self.all_alone = True
                return
            if self.state.egg_left == -1 :
                self.queue.appendleft(Commands(Action.CONNECT_NBR))
            else :
                self.queue.appendleft(Commands(Action.BROADCAST, 'quit'))
        else :
            self.create_kingdom()

    def decide_action(self):
        if self.give_birth :
            self.handle_mother_queen()
            return
        if len(self.queue) == 0 :
            self.cycle += 1
            if self._can_incant():
                self.queue.appendleft(Commands(Action.INCANTATION))
                return
            if self.state.inventory.get("food", 0) < 2:
                self.queue.appendleft(Commands(Action.TAKE, "food"))
                return
            if self.cycle < 4:
                self.queue.appendleft(Commands(Action.TAKE, "food"))
                return
            else:
                self.cycle = 0
                self.queue.appendleft(Commands(Action.LOOK))

    def _can_incant(self) -> bool:
        if not self.state.vision :
            return False
        requirements = self.state.motivation.LEVEL_REQUIREMENTS.get(self.state.level, {})
        current = self.state.vision[0].split()
        for stone, needed in requirements.items():
            if current.count(stone) < needed:
                return False
        return True

    def handle_broadcast(self, response_list):
        if len(response_list) == 3 and response_list[2] == "quitting":
            self.player_killed += 1
            return True
        return False
