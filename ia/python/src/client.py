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
from src.utils import recv_until_newline
from src.action import Action
from src.server_manager import ServerManager

DIMENSION_X = 0
DIMENSION_Y = 1
PLAYER_LEFT = 1

def get_dimension(dimension_str) :
    dimension_split = dimension_str.split()
    if len(dimension_split) != 2 or not all([val.isdigit() for val in dimension_split]) :
        raise Exception("Invalid dimension from server: %s" % dimension_str)
    dimension_tuple = (int(dimension_split[DIMENSION_X]), int(dimension_split[DIMENSION_Y]))
    return dimension_tuple

def get_client_num(client_num_str) :
    client_num_strip = client_num_str.strip()
    if not client_num_strip.isdigit() :
        raise Exception("Invalid client number left from server: %s" % client_num_str)
    return int(client_num_strip)

class Trantorian (ServerManager) :
    def __init__(self, host, port, team_name):
        ServerManager.__init__(self, host, port)
        self.host = host
        self.port = port
        self.team_name = team_name
        self.dimension = None
        self.player_num = None
        self.player = None
        self.connect()
        
    def connect(self):
        welcome = self.recv()
        if welcome.strip() != "WELCOME":
            raise ConnectionError("Expected WELCOME message.")
        self.sock.sendall(f"{self.team_name}\n".encode())
        self.player_num = get_client_num(self.recv())
        self.dimension = get_dimension(self.recv()) #je ne crois pas qu'on en ait besoin pour le moment mais c'est dans le protocole

    def run(self):
        while True:
            if self.player is not None:
                actions = self.player.decide_action()
                for action in actions:
                    if action != Action.NONE:
                        self.sock.sendall((action + "\n").encode())
            # response = recv_until_newline(self.sock)
            # self.handle_response(response.strip())

    def handle_response(self, response):
        if self.player is None:
            response_list = response.split() # response du serveur -> "message K, text envoyé" -> ex avec notre protocol: "message K, [Queen] role Queen"
            if response_list[3] == "role":
                self.role = ROLE_MAP[response_list[4]]
        else:
            self.player.update(response)
            
    def _spawn_new_client(self):
        subprocess.Popen(["./zappy_ai", "-p", self.port, "-n", self.team_name, "-h", self.host])
