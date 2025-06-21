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
from src.utils import recv_until_newline
from src.action import Action, Commands
from src.server_manager import ServerManager

DIMENSION_X = 0
DIMENSION_Y = 1
PLAYER_LEFT = 1



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
            Action.FORWARD: self.void,
            Action.LEFT: self.void,
            Action.RIGHT: self.void,
            Action.LOOK: self.void,
            Action.INVENTORY: self.void,
            Action.BROADCAST: self.void,
            Action.TAKE: self.void,
            Action.SET: self.void,
            Action.FORK: self._spawn_new_client,
            Action.INCANTATION: self.void,
            Action.CONNECT_NBR: self.void,
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
                print("Turn, " , i)
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
        if self.player.handle_broadcast(response_list):
            self.player = ROLE_MAP[response_list[3]]
            return True
        return False

    def handle_response(self, response: str) -> bool:
        response_list = response.split()
        if isinstance(self.player, Nobody):
            if self.player.cycle > 5:
                self.player = ROLE_MAP["First_Queen"]
                return True
        if response_list[0] == "message":
            if isinstance(self.player, Nobody): # response du serveur -> "message K, text envoyé" -> ex avec notre protocol: "message K, [Queen] role Queen"
                return self.handle_nobody(response_list)
            return self.player.handle_broadcast(response_list)
        elif self.player.last_sent:
            if response_list[0] == Commands.COMMANDS[self.player.last_sent]["response success"][0]:
                self.COMMANDS[self.player.last_sent]()
            self.player.state.update(response)
            return True

    def _spawn_new_client(self) -> None:
        subprocess.Popen(["./zappy_ai", "-p", str(self.port), "-n", self.team_name, "-h", self.host])
        
    def void(self):
        return
