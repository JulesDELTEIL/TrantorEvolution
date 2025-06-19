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
        self.player = Nobody()
        self.connect()
        
    def connect(self):
        welcome = self.recv()
        if welcome.strip() != "WELCOME":
            raise ConnectionError("Expected WELCOME message.")
        self.sock.sendall(f"{self.team_name}\n".encode())
        self.player_num = get_client_num(self.recv())
        self.dimension = get_dimension(self.recv()) #je ne crois pas qu'on en ait besoin pour le moment mais c'est dans le protocole

    def send_action(self):
        if len(self.player.queue) == 0 :
            self.player.decide_action()
        action = self.player.queue.popleft()
        self.send((action.__str__() + "\n").encode())

    def analyse_requests(self, message):
        message_left = message
        while message_left:
            index = message_left.find("\n")
            if index == -1:
                break
            if self.handle_response(message_left) :
                self.send_action()
            message_left = message_left[index + 1:]
        return message_left

    def run(self):
        self.send_action()
        while True:
            response = self.recv()
            if not response :
                break
            self.analyse_requests(response)


    def handle_nobody(self, response_list):
        print("stp")
        if self.player.handle_broadcast(response_list):
            self.player = ROLE_MAP[response_list[4]]
            return True
        return False

    def handle_response(self, response):
        response_list = response.split()
        if isinstance(self.player, Nobody):
            if self.player.cycle > 5:
                print("allezzzzzzz")
                self.player = ROLE_MAP["First_Queen"]
                return True
        if response_list[0] == "message":
            if isinstance(self.player, Nobody): # response du serveur -> "message K, text envoyé" -> ex avec notre protocol: "message K, [Queen] role Queen"
                return self.handle_nobody(response_list)
            return False
        else:
            self.player.state.update(response)
            return True

    def _spawn_new_client(self):
        subprocess.Popen(["./zappy_ai", "-p", self.port, "-n", self.team_name, "-h", self.host])
