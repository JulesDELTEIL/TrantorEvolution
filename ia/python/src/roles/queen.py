##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## queenRole.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action
from src.macros import LEVEL_REQUIREMENTS

class Queen(BaseRole):
    def __init__(self, *inp):
        super().__init__()
        if len(inp) == 1:
            print("------------- JE SUIS UNE REINE MERE------------")
            self._birth_function = inp[0]
            self._waiting_for_slot_number = True
            self._give_birth = True
            self._egg_left = -1
        else:
            print("------------- JE SUIS UNE REINE ------------")
            self._give_birth = False
        self._all_alone = False
        self._player_killed = 0
        self._last_incantation = 0
        self._incant_asked = False

    def _create_kingdom(self):
        for _ in range(3):
            self._queue.appendleft(Commands(Action.FORK))
            self._queue.appendleft(Commands(Action.BROADCAST, 'role;queen'))
        self._queue.appendleft(Commands(Action.FORK))
        self._queue.appendleft(Commands(Action.BROADCAST, 'role;foreman'))
        self._queue.appendleft(Commands(Action.FORK))
        self._queue.appendleft(Commands(Action.BROADCAST, 'role;matriarch'))
        self._queue.appendleft(Commands(Action.LEFT))
        self._give_birth = False

    def _fill__egg_left(self):
        for _ in range(self._egg_left):
            self._birth_function()

    def _handle_mother_queen(self):
        if not self._all_alone:
            if self._egg_left == -1 and self._waiting_for_slot_number:
                self._queue.appendleft(Commands(Action.CONNECT_NBR))
                return
            else:
                if self._player_killed >= self._egg_left or self._waiting_for_slot_number and not self._egg_left:
                    self._all_alone = True
                    self._create_kingdom()
                    return
                if self._waiting_for_slot_number:
                    self._fill__egg_left()
                    self._waiting_for_slot_number = False
                self._queue.appendleft(Commands(Action.BROADCAST, 'quit'))
        else:
            print("<QUEEN> : Creating kingdom")
            self.create_kingdom()

    def decide_action(self):
        if self._give_birth:
            self._handle_mother_queen()
            return
        self._cycle += 1
        if self._incant_asked == False and self._can_incant():
            self._queue.appendleft(Commands(Action.INCANTATION))
            self._incant_asked = True
            return
        self._incant_asked = False
        self._queue.appendleft(Commands(Action.LOOK))
        for _ in range (5):
            self._queue.appendleft(Commands(Action.LEFT))
        self._queue.appendleft(Commands(Action.TAKE, "food"))

    def _can_incant(self) -> bool:
        print("Can i incant ?")
        if self._cycle - self._last_incantation < 15 or (self._level < 2 and self._cycle < 50):
            return False
        if not self._last_vision or self._last_vision.count('player') < 6:
            return False
        requirements = LEVEL_REQUIREMENTS.get(self._level, {})
        print("last vision:", self._last_vision)
        for stone in requirements.keys():
            print("stone:", stone, " count:", self._last_vision.count(stone), " - required:", requirements[stone])
            if self._last_vision.count(stone) < requirements[stone]:
                return False
        print("je veux incanter", self._level)
        return True

    def handle_broadcast(self, response_list: list[str]) -> bool:
        if len(response_list) == 3 and response_list[2] == "quitting":
            self._player_killed += 1
            return True
        return False
