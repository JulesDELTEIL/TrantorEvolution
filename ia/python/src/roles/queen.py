##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## queenRole.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action
from src.macros import LEVEL_REQUIREMENTS, BROADCAST_MSG
from src.cypher import open_rockyou_file, crack_fernet

class Queen(BaseRole):
    """
    If Mother Queen, create the kindom (3 queens, 1 foreman, 1 matriarch).
    
    A classic queen look to incant.
    """
    def __init__(self, *inp):
        super().__init__()
        if len(inp) == 1:
            self._birth_function = inp[0]
            self._waiting_for_slot_number: bool = True
            self._give_birth: bool = True
            self._egg_left: int = -1
        else:
            self._give_birth: bool = False
        self._all_alone: bool = False
        self._player_killed: int = 0
        self._last_incantation: int = 0
        self._incant_asked: bool = False
        self._wordlist: list[str] = open_rockyou_file()
        self._key_opponent: str = None

    def _create_kingdom(self):
        for _ in range(3):
            self._queue.appendleft(Commands(Action.FORK))
            self._queue.appendleft(Commands(Action.BROADCAST, 'role;queen'))
            self._queue.appendleft(Commands(Action.LEFT))
        self._queue.appendleft(Commands(Action.LEFT))
        self._queue.appendleft(Commands(Action.FORK))
        self._queue.appendleft(Commands(Action.BROADCAST, 'role;foreman'))
        self._queue.appendleft(Commands(Action.LEFT))
        self._queue.appendleft(Commands(Action.FORK))
        self._queue.appendleft(Commands(Action.BROADCAST, 'role;matriarch'))
        self._queue.appendleft(Commands(Action.LEFT))
        self._give_birth = False

    def _fill__egg_left(self) -> None:
        for _ in range(self._egg_left):
            self._birth_function()

    def _handle_mother_queen(self) -> None:
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
            self.create_kingdom()

    def decide_action(self) -> None:
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
        for _ in range(4):
            self._queue.appendleft(Commands(Action.LEFT))
        if self._key_opponent:
            self._queue.appendleft(Commands(Action.BROADCAST, 'quit'))
        else:
            self._queue.appendleft(Commands(Action.LEFT))
        self._queue.appendleft(Commands(Action.LOOK))
        self._queue.appendleft(Commands(Action.TAKE, "food"))

    def _can_incant(self) -> bool:
        if self._cycle - self._last_incantation < 15 or (self._level < 2 and self._cycle < 50):
            return False
        if not self._last_vision or self._last_vision.count('player') < 6:
            return False
        requirements = LEVEL_REQUIREMENTS.get(self._level, {})
        for stone in requirements.keys():
            if self._last_vision.count(stone) < requirements[stone]:
                return False
        return True

    def handle_broadcast(self, response_list: list[str]) -> bool:
        if len(response_list) == 3 and response_list[2] == "quitting":
            self._player_killed += 1
            return True
        if response_list[2] not in BROADCAST_MSG and self._wordlist:
            self._key_opponent = crack_fernet(response_list[2], self._wordlist)
        return False
