##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## player.py
##

from src.roles.nobody import Nobody
from src.action import Action
from src.utils import parse_vision, parse_inventory
from src.macros import X, Y

import subprocess

class Player():
    def __init__(self, host: str, port: str, team_name: str):
        self._player_host = host
        self._player_port = port
        self._player_team_name = team_name
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
            Action.INCANTATION: self._incatation_succes,
            Action.CONNECT_NBR: self._update_connect_nbr,
            Action.EJECT: self._void,
            Action.NONE:self._void
        }
    
    def _spawn_new_client(self) -> None:
        subprocess.Popen(["./zappy_ai", "-p", self._player_port, "-n", self._player_team_name, "-h", self._player_host])

    def _update_connect_nbr(self, connect_nbr: str) -> bool:
        print("UPDATING CONNECT NBR gotten", connect_nbr)
        self.role._egg_left = int(connect_nbr)
        return True

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
        self.role._last_inventory = parse_inventory(response)
        
    def _turn_left(self):
        if self.role._direction is not None:
            mapping = {"up": "left", "left": "down", "down": "right", "right": "up"}
            self.role._direction = mapping[self.role._direction]

    def _turn_right(self):
        if self.role._direction is not None:
            mapping = {"up": "right", "right": "down", "down": "left", "left": "up"}
            self.role._direction = mapping[self.role._direction]

    def _move_forward(self):
        if self.role._direction == "up":
            self.role.pos[Y] += 1
        elif self.role._direction == "right":
            self.role.pos[X] += 1
        elif self.role._direction == "down":
            self.role.pos[Y] -= 1
        elif self.role._direction == "left":
            self.role.pos[X] -= 1
            
    def _take_object(self, response: str):
        if response == "ko" or response == "ko\n":
            self.role.carry = None
            self.role._last_vision = None
        else:
            self.role.mode = 'DELIVERING'
    
    def _incatation_succes(self, response: str):
        if response == "Elevation underway":
            return
        response_list = response.split()
        if response_list[0] == "Current":
            self.role._level = int(response_list[2])
            self.role._last_incantation = self.role._cycle

    def _void(self):
        return
