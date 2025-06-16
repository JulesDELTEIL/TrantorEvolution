##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## client.py
##

import socket
import subprocess
from src.roles.role_map import ROLE_MAP
from src.utils import recv_until_newline
from src.action import Action

class Trantorian:
    def __init__(self, host, port, team_name):
        self.host = host
        self.port = port
        self.team_name = team_name
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.player = None
        
    def connect(self):
        self.sock.connect((self.host, self.port))
        welcome = recv_until_newline(self.sock)
        if welcome.strip() != "WELCOME":
            raise ConnectionError("Expected WELCOME message.")
        self.sock.sendall(f"{self.team_name}\n".encode())
        dimension = recv_until_newline(self.sock) #je ne crois pas qu'on en ait besoin pour le moment mais c'est dans le protocole

    def run(self):
        #self.connect()
        while True:
            if self.player is not None:
                actions = self.player.decide_action()
                for action in actions:
                    if action != Action.NONE:
                        self.sock.sendall((action + "\n").encode())
            #response = recv_until_newline(self.sock)
            #self.handle_response(response.strip())

    def handle_response(self, response):
        if self.player is None:
            response_list = response.split() # response du serveur -> "message K, text envoyé" -> ex avec notre protocol: "message K, [Queen] role Queen"
            if response_list[3] == "role":
                self.role = ROLE_MAP[response_list[4]]
        else:
            self.player.update(response)
            
    def _spawn_new_client(self):
        subprocess.Popen(["./zappy_ai", "-p", self.port, "-n", self.team_name, "-h", self.host])
