##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## communication.py
##

import socket

import src.cypher as cyp
from src.roles.role_map import ROLE_MAP
from src.roles.nobody import Nobody
from src.roles.queen import Queen
from src.macros import X, Y
from src.action import Action, Commands

class Communication():
    """
    Manage all things received via server and send things AI want to.
    """
    def __init__(self, team_name: str, sock):
        self._communication_team_name = team_name
        self._communication_sock = sock
        self._dimension = None
        self._player_num = None
        self._connect_function = [
            self._get_welcome,
            self._get_client_num,
            self._get_dimension,
        ]
        self._connect()

    def _get_client_num(self, client_num_str: str) -> None:
        client_num_strip = client_num_str.strip()
        if not client_num_strip.isdigit():
            raise ValueError("Invalid client number left from server: %s" % client_num_str)
        self._player_num = int(client_num_strip)

    def _get_dimension(self, dimension_str: str) -> None:
        dimension_split = dimension_str.split()
        if len(dimension_split) != 2 or not all([val.isdigit() for val in dimension_split]):
            raise ValueError("Invalid dimension from server: %s" % dimension_str)
        dimension_tuple = (int(dimension_split[X]), int(dimension_split[Y]))
        self._dimension = dimension_tuple

    def _get_welcome(self, welcome_str: str) -> None:
        if welcome_str.strip() != "WELCOME":
            raise ConnectionError("Expected WELCOME message.")
        self.send(f"{self._communication_team_name}\n".encode())

    def _connect(self) -> None:
        i = 0
        message = ""
        while i < 3:
            new_message = self.recv()
            if new_message is not None:
                message += new_message
            else:
                exit()
            while message:
                index = message.find("\n")
                if index == -1 or i >= 3:
                    break
                self._connect_function[i](message[:index + 1])
                message = message[index + 1:]
                i += 1

    def send_action(self) -> None:
        if not self.role._queue:
            self.role.decide_action()
        if self.role._queue:
            action = self.role._queue.pop()
            if action.action == Action.BROADCAST:
                if isinstance(self.role, Queen):
                    if self.role._key_opponent and action.argument == 'quit':
                        action.argument = cyp.cypher(action.argument, self.role._key_opponent)
                    else:
                        action.argument = cyp.cypher(action.argument, self._communication_team_name)
                else:
                    action.argument = cyp.cypher(action.argument, self._communication_team_name)
            if action.action != Action.NONE:
                self.send((action.__str__() + "\n").encode())
                self.role._last_sent = action.action

    def analyse_requests(self, message: str) -> str:
        message_left = message
        while message_left:
            index = message_left.find("\n")
            if index == -1:
                break
            if message_left[:index + 1] == "dead\n":
                self._communication_sock.shutdown(socket.SHUT_RDWR)
                self._communication_sock.close()
                exit()
            if self._handle_response(message_left[:index + 1]):
                self.send_action()
            message_left = message_left[index + 1:]
        return message_left

    def run(self) -> None:
        self.send_action()
        response = ""
        while True:
            new_response = self.recv()
            if new_response is not None:
                response += new_response
            if not response:
                break
            response = self.analyse_requests(response)


    def _translate_broadcast(self, response_list: list[str]) -> list[str]:
        real_broadcast = []
        broadcast_message = cyp.decypher(response_list[2], self._communication_team_name)
        if not broadcast_message:
            return []
        for i in range(2):
            real_broadcast.append(response_list[i])
        for item in broadcast_message.split():
            real_broadcast.append(item)
        return real_broadcast

    def _handle_action(self, response: str, response_list: list[str]) -> bool:
        if response_list[0] == "Current":
            self._incantation_success(response)
        elif self.role._last_sent:
            if response_list[0][0] == '[':
                if self.role._last_sent == Action.LOOK or self.role._last_sent == Action.INVENTORY:
                    self.COMMANDS[self.role._last_sent](response)
            if ((self.role._last_sent == Action.CONNECT_NBR and response_list[0].isdigit())
                    or response_list[0] == Commands.COMMANDS[self.role._last_sent]["response success"][0]):
                self.COMMANDS[self.role._last_sent](response)
            return True
        return True

    def handle_nobody(self, response: str) -> bool:
        response_list = response.split()
        if response_list[0] == "message":
            deciphered_broadcast = self._translate_broadcast(response_list)
            if not deciphered_broadcast:
                return False
            broadcast = self.role.handle_broadcast(deciphered_broadcast)
            if broadcast == "ROLE":
                self.role = ROLE_MAP[deciphered_broadcast[2][5:]]()
            elif broadcast == "QUIT":
                action = Commands(Action.BROADCAST, cyp.cypher("quitting", self._communication_team_name))
                self.role._last_sent = action.action
                self.send((action.__str__() + "\n").encode())
            return False
        if not self.role._is_there_anyone:
            if self.role._cycle > 10:
                self.role = Queen(lambda: self._spawn_new_client(response))
                return True
        if self.role._last_sent == Action.BROADCAST and response_list[0] == "ok":
            self._communication_sock.shutdown(socket.SHUT_RDWR)
            self._communication_sock.close()
            exit()
        return self._handle_action(response, response_list)

    def _handle_response(self, response: str) -> bool:
        response_list = response.split()
        if isinstance(self.role, Nobody):
            return self.handle_nobody(response)
        if response_list[0] == "message":
            deciphered_broadcast = self._translate_broadcast(response_list)
            if deciphered_broadcast:
                if deciphered_broadcast[2] == 'quit':
                    self._communication_sock.shutdown(socket.SHUT_RDWR)
                    self._communication_sock.close()
                    exit()
                else:
                    self.role.handle_broadcast(deciphered_broadcast)
            else:
                if response_list[2] == 'quit':
                    self._communication_sock.shutdown(socket.SHUT_RDWR)
                    self._communication_sock.close()
                    exit()
                else:
                    self.role.handle_broadcast(response_list)
            return False
        return self._handle_action(response, response_list)
