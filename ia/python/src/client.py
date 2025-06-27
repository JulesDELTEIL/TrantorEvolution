##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## client.py
##

import socket
import subprocess

import src.cypher as cyp
from src.roles.role_map import ROLE_MAP
from src.roles.nobody import Nobody
from src.roles.queen import Queen
from src.utils import parse_vision, parse_inventory
from src.macros import X, Y
from src.action import Action, Commands
from src.server_manager import ServerManager
from enum import Enum

class Direction(Enum):
    UP = "up"
    DOWN = "down"
    LEFT = "left"
    RIGHT = "right"

class Trantorian(ServerManager):
    def __init__(self, host, port, team_name):
        ServerManager.__init__(self, host, port)
        self._host = host
        self._port = port
        self._team_name = team_name
        self._dimension = None
        self._player_num = None
        self._player = Nobody()
        self._connect_function = [
            self._get_welcome,
            self._get_client_num,
            self._get_dimension,
        ]
        self._connect()
        self.COMMANDS = {
            Action.FORWARD: self._move_forward,
            Action.LEFT: self._turn_left,
            Action.RIGHT: self._turn_right,
            Action.LOOK: self._update_mindmap,
            Action.INVENTORY: self._update_inventory,
            Action.BROADCAST: self.void,
            Action.TAKE: self._take_object,
            Action.SET: self.void,
            Action.FORK: self._spawn_new_client,
            Action.INCANTATION: self._incatation_succes,
            Action.CONNECT_NBR: self.update_connect_nbr,
            Action.EJECT: self.void,
            Action.NONE:self.void
        }

    def _get_client_num(self, client_num_str: str) -> None:
        client_num_strip = client_num_str.strip()
        if not client_num_strip.isdigit():
            raise Exception("Invalid client number left from server: %s" % client_num_str)
        self._player_num = int(client_num_strip)

    def _get_dimension(self, dimension_str: str) -> None:
        dimension_split = dimension_str.split()
        if len(dimension_split) != 2 or not all([val.isdigit() for val in dimension_split]):
            raise Exception("Invalid dimension from server: %s" % dimension_str)
        dimension_tuple = (int(dimension_split[X]), int(dimension_split[Y]))
        self._dimension = dimension_tuple

    def _get_welcome(self, welcome_str: str) -> None:
        if welcome_str.strip() != "WELCOME":
            raise ConnectionError("Expected WELCOME message.")
        self.send(f"{self._team_name}\n".encode())

    def _connect(self) -> None:
        i = 0
        message = ""
        while i < 3:
            message += self.recv()
            while message:
                index = message.find("\n")
                if index == -1 or i >= 3:
                    break
                self._connect_function[i](message[:index + 1])
                message = message[index + 1:]
                i += 1

    def send_action(self) -> None:
        if not self._player._queue:
            self._player.decide_action()
        if self._player._queue:
            action = self._player._queue.pop()
            if action.action == Action.BROADCAST:
                action.argument = cyp.cypher(action.argument, self._team_name)
            if action.action != Action.NONE:
                self.send((action.__str__() + "\n").encode())
                self._player._last_sent = action.action

    def analyse_requests(self, message: str) -> str:
        message_left = message
        while message_left:
            index = message_left.find("\n")
            if index == -1:
                break
            if message == "dead" or message == "dead\n":
                self._sock.shutdown(socket.SHUT_RDWR)
                self._sock.close()
                exit()
            if self.handle_response(message_left[:index + 1]):
                self.send_action()
            message_left = message_left[index + 1:]
        return message_left

    def run(self) -> None:
        self.send_action()
        while True:
            response = self.recv()
            if not response:
                break
            self.analyse_requests(response)

    def handle_nobody(self, response_list: list[str]) -> bool:
        broadcast = self._player.handle_broadcast(response_list)
        if broadcast == "ROLE":
            print(response_list[2][5:])
            self._player = ROLE_MAP[response_list[2][5:]]()
            return False
        if broadcast == "QUIT":
            action = Commands(Action.BROADCAST, cyp.cypher("quitting", self._team_name))
            self._player._last_sent = action.action
            self.send((action.__str__() + "\n").encode())
        return False


    def translate_broadcast(self, response_list: list[str]) -> list[str]:
        real_broadcast = []
        broadcast_message = cyp.decypher(response_list[2], self._team_name)
        if not broadcast_message:
            return []
        for i in range(2):
            real_broadcast.append(response_list[i])
        for item in broadcast_message.split():
            real_broadcast.append(item)
        return real_broadcast

    def handle_response(self, response: str) -> bool:
        response_list = response.split()
        if isinstance(self._player, Nobody) and self._player._is_there_anyone == False:
            if self._player._cycle > 10:
                self._player = Queen(lambda: self._spawn_new_client())
                return True
        if response_list[0] == "message":
            deciphered_broadcast = self.translate_broadcast(response_list)
            if not deciphered_broadcast:
                return False
            if isinstance(self._player, Nobody):
                return self.handle_nobody(deciphered_broadcast)
            self._player.handle_broadcast(deciphered_broadcast)
            return False
        if response_list[0] == "Current":
            self._player._level = int(response_list[2])
            self._player._last_incantation = self._player._cycle
            return True
        elif self._player._last_sent:
            if self._player._last_sent == Action.CONNECT_NBR and response_list[0].isdigit():
                return self.COMMANDS[self._player._last_sent](response_list[0])
            if response_list[0][0] == '[':
                if self._player._last_sent == Action.LOOK or self._player._last_sent == Action.INVENTORY:
                    self.COMMANDS[self._player._last_sent](response)
            if self._player._last_sent == Action.BROADCAST and response_list[0] == "ok" and isinstance(self._player, Nobody):
                self._sock.shutdown(socket.SHUT_RDWR)
                self._sock.close()
                exit()
            if self._player._last_sent == Action.INCANTATION or self._player._last_sent == Action.TAKE or response_list[0] == "Current":
                self.COMMANDS[self._player._last_sent](response)
            elif response_list[0] == Commands.COMMANDS[self._player._last_sent]["response success"][0]:
                self.COMMANDS[self._player._last_sent]()
            return True
        return True

    def _spawn_new_client(self) -> None:
        subprocess.Popen(["./zappy_ai", "-p", str(self._port), "-n", self._team_name, "-h", self._host])

    def update_connect_nbr(self, connect_nbr: str) -> bool:
        print("UPDATING CONNECT NBR gotten", connect_nbr)
        self._player._egg_left = int(connect_nbr)
        return True

    def _update_mindmap(self, response: str) -> None:
        response_formatted = parse_vision(response)
        self._player._last_vision = response_formatted[0]
        if isinstance(self._player, Nobody):
            if self._player._last_vision.count("player") > 1:
                self._player._is_there_anyone = True
            else:
                self._player._is_there_anyone = False
        self._player._map.update_mindmap(response_formatted, self._player._level, self._player._cycle, self._player.pos)
        
    def _update_inventory(self, response: str) -> None:
        self._player._last_inventory = parse_inventory(response)
        
    def _turn_left(self):
        if self._player._direction is not None:
            mapping = {"up": "left", "left": "down", "down": "right", "right": "up"}
            self._player._direction = mapping[self._player._direction]

    def _turn_right(self):
        if self._player._direction is not None:
            mapping = {"up": "right", "right": "down", "down": "left", "left": "up"}
            self._player._direction = mapping[self._player._direction]

    def _move_forward(self):
        if self._player._direction == "up":
            self._player.pos[1] += 1
        elif self._player._direction == "right":
            self._player.pos[0] += 1
        elif self._player._direction == "down":
            self._player.pos[1] -= 1
        elif self._player._direction == "left":
            self._player.pos[0] -= 1
            
    def _take_object(self, response: str):
        if response == "ko" or response == "ko\n":
            self._player.carry = None
            self._player._last_vision = None
        else:
            self._player.mode = 'DELIVERING'
    
    def _incatation_succes(self, response: str):
        if response == "Elevation underway":
            return
        response_list = response.split()
        if response_list[0] == "Current":
            self._player._level = int(response_list[2])
            self._player._last_incantation = self._player._cycle

    def void(self):
        return
