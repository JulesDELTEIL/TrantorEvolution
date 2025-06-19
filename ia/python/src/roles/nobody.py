##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## nobody.py
##

from itertools import cycle
import socket
from src.roles.base_role import BaseRole
from src.action import Commands, Action
from src.roles.role_map import ROLE_MAP
class Unknown(BaseRole):
    def __init__(self):
        super().__init__()

    def handle_broadcast(self, response_list):
        if response_list[3] == "role" and (response_list[3][:1] == "0"):
            return True
        if response_list[3] == "stop":
            self.sock.shutdown(socket.SHUT_RDWR)
            self.sock.close()
            return False
        return False


    def decide_action(self):
        if self.queue.empty():
            self.queue.appendleft(Commands.LEFT)