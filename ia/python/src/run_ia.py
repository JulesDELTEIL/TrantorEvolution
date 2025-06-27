#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## Indentify and run ai behaviour
#

PORT = 1
NAME = 2
ARG_NB = 3
ERROR = 84

from server_manager import ServerManager
import sys

def analyse_requests (message):
    message_left = message
    while message_left:
        index = message_left.find("\n")
        if index == -1:
            break
        print("MESSAGE:", message_left[:index + 1])
        message_left = message_left[index + 1:]
    return message_left

def initialize_ia():
    if len(sys.argv) != ARG_NB:
        exit(ERROR)
    client = ServerManager(sys.argv[PORT], int(sys.argv[NAME]))
    message = ""
    while True:
        message += client.recv()
        if not message:
            break
        message = analyse_requests(message)

