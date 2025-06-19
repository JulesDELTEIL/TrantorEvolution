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

class Nobody(BaseRole):
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
<<<<<<< HEAD
            self.queue.appendleft(Commands.LEFT)
=======
            self.queue.appendleft(Commands(Action.LEFT))
>>>>>>> f301efde58287caca30101ebf1643ffe0df12226
