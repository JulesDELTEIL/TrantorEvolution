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
        print("------------- JE SUIS UNE REINE ------------")
        if len(inp) == 1 :
            print("MORE THAN ONE ARG")
            self.birth_function = inp[0]
            self.waiting_for_slot_number = True
            self.give_birth = True
        else :
            self.give_birth = False
        self.all_alone = False
        self.player_killed = 0

    def create_kingdom(self):
        print("len queue --------------- %i ------" % len(self.queue))
        for _ in range(5):
            self.queue.appendleft(Commands(Action.FORK))
            self.queue.appendleft(Commands(Action.BROADCAST, 'role queen'))
            print("FOOOOOOOOOOOOOOOORK QUEEEEEEEEEEEEN")
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'role foreman'))
        self.queue.appendleft(Commands(Action.FORK))
        self.queue.appendleft(Commands(Action.BROADCAST, 'role matriarch'))
        self.give_birth = False


    def fill_egg_left(self):
        for _ in range(self.state.egg_left) :
            print("FIll egg new")
            self.birth_function()

    def handle_mother_queen(self):
        if not self.all_alone :
            if self.state.egg_left == -1 and self.waiting_for_slot_number:
                print("Asking for whoes still here")
                self.queue.appendleft(Commands(Action.CONNECT_NBR))
                return
            else :
                if self.player_killed >= self.state.egg_left or self.waiting_for_slot_number and not self.state.egg_left:
                    print("Finally alone with", self.state.egg_left, "left")
                    self.all_alone = True
                    self.create_kingdom()
                    return
                if self.waiting_for_slot_number :
                    print("Filling slots left")
                    self.fill_egg_left()
                    self.waiting_for_slot_number = False
                print("Asking them to kys", self.player_killed)
                self.queue.appendleft(Commands(Action.BROADCAST, 'quit'))
            print("Not alone")
        else :
            print("Creating kingdom------------------------------------------------------------------")
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
            if self.cycle < 4:
                self.queue.appendleft(Commands(Action.TAKE, "food"))
                return
            else:
                self.cycle = 0
                self.queue.appendleft(Commands(Action.BROADCAST, "here"))
                self.queue.appendleft(Commands(Action.LOOK))

    def _can_incant(self) -> bool:
        if not self.state.last_vision :
            return False
        requirements = self.state.motivation.LEVEL_REQUIREMENTS.get(self.state.level, {})
        current = self.state.last_vision[0].split()
        for stone, needed in requirements.items():
            if current.count(stone) < needed:
                return False
        return True

    def handle_broadcast(self, response_list: list[str]) -> bool:
        print("queen received ", response_list)
        if len(response_list) == 3 and response_list[2] == "quitting":
            self.player_killed += 1
            return True
        return False
