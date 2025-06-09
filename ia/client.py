##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## client.py
##

import socket
from player import PlayerState
from strategy import decide_next_action
from utils import recv_until_newline
from action import Action

class Trantorian:
    def __init__(self, host, port, team_name):
        self.host = host
        self.port = port
        self.team_name = team_name
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.buffer = ""
        self.player = PlayerState()
        
    def connect(self):
        self.sock.connect((self.host, self.port))
        welcome = recv_until_newline(self.sock)
        if welcome.strip() != "WELCOME":
            raise ConnectionError("Expected WELCOME message.")
        self.sock.sendall(f"{self.team_name}\n".encode())

    def run(self):
        self.connect()
        while True:
            action = decide_next_action(self.player)
            if action and action != Action.NONE:
                self.sock.sendall((action + "\n").encode())
            response = recv_until_newline(self.sock)
            self.handle_response(response.strip())

    def handle_response(self, response):
        self.player.update(response)
