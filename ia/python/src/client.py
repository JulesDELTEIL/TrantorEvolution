##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## client.py
##

import socket
import subprocess
from curses.ascii import isdigit
from sqlite3 import connect

from src.roles.role_map import ROLE_MAP
from src.roles.nobody import Nobody
from src.roles.queen import Queen
from src.utils import recv_until_newline
from src.action import Action, Commands
from src.server_manager import ServerManager
from enum import Enum

DIMENSION_X = 0
DIMENSION_Y = 1
PLAYER_LEFT = 1

class Direction(Enum):
    UP = "up"
    DOWN = "down"
    LEFT = "left"
    RIGHT = "right"

class Trantorian (ServerManager) :
    def __init__(self, host, port, team_name):
        ServerManager.__init__(self, host, port)
        self.host = host
        self.port = port
        self.team_name = team_name
        self.dimension = None
        self.player_num = None
        self.player = Nobody()
        self.connect_function = [
            self.get_welcome,
            self.get_client_num,
            self.get_dimension,
        ]
        self.connect()
        self.COMMANDS = {
            Action.FORWARD: self._move_forward,
            Action.LEFT: self._turn_left,
            Action.RIGHT: self._turn_right,
            Action.LOOK: self._update_mindmap,
            Action.INVENTORY: self.player.state.parse_inventory,
            Action.BROADCAST: self.void,
            Action.TAKE: self.void,
            Action.SET: self.void,
            Action.FORK: self._spawn_new_client,
            Action.INCANTATION: self._incatation_succes,
            Action.CONNECT_NBR: self.update_connect_nbr,
            Action.EJECT: self.void,
            Action.NONE:self.void
        }

    def get_client_num(self, client_num_str: str) -> None:
        client_num_strip = client_num_str.strip()
        if not client_num_strip.isdigit() :
            raise Exception("Invalid client number left from server: %s" % client_num_str)
        self.player_num = int(client_num_strip)

    def get_dimension(self, dimension_str: str) -> None:
        dimension_split = dimension_str.split()
        if len(dimension_split) != 2 or not all([val.isdigit() for val in dimension_split]) :
            raise Exception("Invalid dimension from server: %s" % dimension_str)
        dimension_tuple = (int(dimension_split[DIMENSION_X]), int(dimension_split[DIMENSION_Y]))
        self.dimension = dimension_tuple

    def get_welcome(self, welcome_str: str) -> None:
        if welcome_str.strip() != "WELCOME":
            raise ConnectionError("Expected WELCOME message.")
        self.send(f"{self.team_name}\n".encode())

    def connect(self) -> None:
        i = 0
        message = ""
        while i < 3 :
            message += self.recv()
            while message :
                index = message.find("\n")
                if index == -1:
                    break
                self.connect_function[i](message[:index + 1])
                message = message[index + 1:]
                i += 1

    def send_action(self) -> None:
        if not self.player.queue :
            self.player.decide_action()
        if self.player.queue :
            action = self.player.queue.pop()
            self.send((action.__str__() + "\n").encode())
            self.player.last_sent = action.action

    def analyse_requests(self, message: str) -> str:
        message_left = message
        while message_left:
            index = message_left.find("\n")
            if index == -1:
                break
            if self.handle_response(message_left[:index + 1]) :
                self.send_action()
            message_left = message_left[index + 1:]
        return message_left

    def run(self) -> None:
        self.send_action()
        while True:
            response = self.recv()
            if not response :
                break
            self.analyse_requests(response)

    def handle_nobody(self, response_list: list[str]) -> bool:
     broadcast = self.player.handle_broadcast(response_list)
     if broadcast  == "ROLE":
            self.player = ROLE_MAP[response_list[3]]
            return True
     if broadcast == "QUIT":
         action = Commands(Action.BROADCAST, 'quitting')
         self.send((action.__str__() + "\n").encode())
     return False

    def handle_response(self, response: str) -> bool:
        response_list = response.split()
        if isinstance(self.player, Nobody):
            if self.player.cycle > 5:
                print("Becoming a queen")
                self.player = Queen(lambda : self._spawn_new_client())
                return True
        if response_list[0] == "message":
            if isinstance(self.player, Nobody): # response du serveur -> "message K, text envoyé" -> ex avec notre protocol: "message K, [Queen] role Queen"
                return self.handle_nobody(response_list)
            return self.player.handle_broadcast(response_list)
        elif self.player.last_sent:
            if self.player.last_sent == Action.CONNECT_NBR and response_list[0].isdigit():
                return self.COMMANDS[self.player.last_sent](response_list[0])
            if response_list[0][0] == '[':
                if self.player.last_sent == Action.LOOK or self.player.last_sent == Action.INVENTORY:
                    self.COMMANDS[self.player.last_sent](response)
            if self.player.last_sent == Action.BROADCAST and response_list[0] == "ok" and isinstance(self.player, Nobody)  :
                self.sock.shutdown(socket.SHUT_RDWR)
                self.sock.close()
            if self.player.last_sent == Action.INCANTATION:
                self.COMMANDS[self.player.last_sent](response)
            if response_list[0] == Commands.COMMANDS[self.player.last_sent]["response success"][0]:
                self.COMMANDS[self.player.last_sent]()
            self.player.state.update(response)
            return True
        return False

    def _spawn_new_client(self) -> None:
        subprocess.Popen(["./zappy_ai", "-p", str(self.port), "-n", self.team_name, "-h", self.host])

    def update_connect_nbr(self, connect_nbr: str) -> bool:
        print("UPDATING CONNECT NBR gotten", connect_nbr)
        self.player.state.egg_left = int(connect_nbr)
        return True

    def _update_mindmap(self, response: str) -> None:
        response_formatted = self.state.parse_vision(response)
        self.map.update_mindmap(response_formatted, self.player.state.level, self.player.cycle, self.player.pos)
        
    def _turn_left(self):
        if self.player.direction is not None:
            mapping = {Direction.UP: Direction.LEFT, Direction.LEFT: Direction.DOWN, Direction.DOWN: Direction.RIGHT, Direction.RIGHT: Direction.UP}
            self.player.direction = mapping[self.player.direction]

    def _turn_right(self):
        if self.player.direction is not None:
            mapping = {Direction.UP: Direction.RIGHT, Direction.RIGHT: Direction.DOWN, Direction.DOWN: Direction.LEFT, Direction.LEFT: Direction.UP}
            self.player.direction = mapping[self.player.direction]

    def _move_forward(self):
        if self.player.direction == Direction.UP:
            self.pos[1] -= 1
        elif self.player.direction == Direction.RIGHT:
            self.pos[0] += 1
        elif self.player.direction == Direction.DOWN:
            self.pos[1] += 1
        elif self.player.direction == Direction.LEFT:
            self.pos[0] -= 1
            
    def _incatation_succes(self, response: str):
        if response == "Elevation underway":
            return
        response_list = response.split()
        if response_list[0] == "Current":
            self.player.state.level = int(response_list[2])

    def void(self):
        return
