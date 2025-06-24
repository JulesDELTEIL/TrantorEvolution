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
        if len(inp) == 1 :
            print("")
            print("------------- JE SUIS UNE REINE MERE------------")
            self.birth_function = inp[0]
            self.waiting_for_slot_number = True
            self.give_birth = True
        else :
            print("------------- JE SUIS UNE REINE ------------")
            self.give_birth = False
        self.all_alone = False
        self.player_killed = 0

    def create_kingdom(self):
        for _ in range(5):
            self.queue.appendleft(Commands(Action.FORK))
            self.queue.appendleft(Commands(Action.BROADCAST, 'role;queen'))
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'role;foreman'))
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'role;matriarch'))
        self.give_birth = False


    def fill_egg_left(self):
        for _ in range(self.state.egg_left) :
            self.birth_function()

    def handle_mother_queen(self):
        if not self.all_alone :
            if self.state.egg_left == -1 and self.waiting_for_slot_number:
                self.queue.appendleft(Commands(Action.CONNECT_NBR))
                return
            else :
                if self.player_killed >= self.state.egg_left or self.waiting_for_slot_number and not self.state.egg_left:
                    self.all_alone = True
                    self.create_kingdom()
                    return
                if self.waiting_for_slot_number :
                    self.fill_egg_left()
                    self.waiting_for_slot_number = False
                self.queue.appendleft(Commands(Action.BROADCAST, 'quit'))
        else :
            print("<QUEEN> : Creating kingdom")
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
            if self.cycle > 4:
                self.queue.appendleft(Commands(Action.TAKE, "food"))
                self.cycle = 0
                return
            else:
                self.queue.appendleft(Commands(Action.LOOK))

    def _can_incant(self) -> bool:
        if not self.state.last_vision :
            return False
        requirements = self.state.motivation.LEVEL_REQUIREMENTS.get(self.state.level, {})
        current = self.state.last_vision
        for stone in requirements.keys():
            if current.count(stone) < requirements[stone]:
                return False
        return True

    def handle_broadcast(self, response_list: list[str]) -> bool:
        if len(response_list) == 3 and response_list[2] == "quitting":
            self.player_killed += 1
            return True
        return False
