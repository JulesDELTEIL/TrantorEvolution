##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## player.py
##

import subprocess

from src.roles.nobody import Nobody
from src.action import Commands, Action
from src.utils import parse_vision, parse_inventory
from src.macros import X, Y

class Player():
    def __init__(self, host: str, port: str, team_name: str):
        self._player_host: str = host
        self._player_port: str = port
        self._player_team_name: str = team_name
        self.role = Nobody()
        self.COMMANDS = {
            Action.FORWARD: self._move_forward,
            Action.LEFT: self._turn_left,
            Action.RIGHT: self._turn_right,
            Action.LOOK: self._update_mindmap,
            Action.INVENTORY: self._update_inventory,
            Action.BROADCAST: self._void,
            Action.TAKE: self._take_object,
            Action.SET: self._void,
            Action.FORK: self._spawn_new_client,
            Action.INCANTATION: self._incantation_success,
            Action.CONNECT_NBR: self._update_connect_nbr,
            Action.EJECT: self._void,
            Action.NONE:self._void
        }
    
    def _spawn_new_client(self, response) -> None:
        subprocess.Popen(["./zappy_ai", "-p", self._player_port, "-n", self._player_team_name, "-h", self._player_host])

    def _update_connect_nbr(self, connect_nbr: str) -> None:
        self.role._egg_left = int(connect_nbr)

    def _update_mindmap(self, response: str) -> None:
        response_formatted = parse_vision(response)
        self.role._last_vision = response_formatted[0]
        if isinstance(self.role, Nobody):
            if self.role._last_vision.count("player") > 1:
                self.role._is_there_anyone = True
            else:
                self.role._is_there_anyone = False
        self.role._map.update_mindmap(response_formatted, self.role._level, self.role._cycle, self.role.pos)
        
    def _update_inventory(self, response: str) -> None:
        self.role.check_eat = False
        self.role._last_inventory = parse_inventory(response)
        if self.role._last_inventory['food'] < 5:
            self.role._queue.clear()
            self.role._queue.appendleft(Commands(Action.TAKE, 'food'))
        self.role._last_vision = None
        if self.role.random.choice([0,1]) == 0:
            self.role._queue.appendleft(Commands(Action.LEFT))
        else:
            self.role._queue.appendleft(Commands(Action.RIGHT))
        self.role._queue.appendleft(Commands(Action.FORWARD))
        self.role._queue.appendleft(Commands(Action.LOOK))
        
    def _turn_left(self, response: str) -> None:
        if self.role._direction is not None:
            mapping = {"up": "left", "left": "down", "down": "right", "right": "up"}
            self.role._direction = mapping[self.role._direction]

    def _turn_right(self, response: str) -> None:
        if self.role._direction is not None:
            mapping = {"up": "right", "right": "down", "down": "left", "left": "up"}
            self.role._direction = mapping[self.role._direction]

    def _move_forward(self, response: str) -> None:
        if self.role._direction == "up":
            self.role.pos[Y] += 1
        elif self.role._direction == "right":
            self.role.pos[X] += 1
        elif self.role._direction == "down":
            self.role.pos[Y] -= 1
        elif self.role._direction == "left":
            self.role.pos[X] -= 1
            
    def _take_object(self, response: str) -> None:
        if response == "ko" or response == "ko\n":
            self.role.carry = None
            self.role._last_vision = None
        else:
            self.role.mode = 'DELIVERING'
    
    def _incantation_success(self, response: str) -> None:
        self.role._queue.clear()
        if response == "Elevation underway":
            return
        response_list = response.split()
        if response_list[0] == "Current":
            self.role._level = int(response_list[2])
            self.role._last_incantation = self.role._cycle
            self.role._incant_asked = False

    def _void(self, response: str) -> None:
        return
