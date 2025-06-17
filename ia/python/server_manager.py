#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## Server Manager
#

import socket
import sys

BUFF_SIZE = 1024
INTERLOCUTOR = 0
MESSAGE_CONTENT = 1
WORD_COUNT = 2

class ServerManager :
    def __init__(self, host : str, port : int) :
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))
        self.last_message = ""

    def send(self, message) :
        self.sock.send(message)

    def recv(self) :
        message = ""
        while not ("\n" in message) :
            message += self.sock.recv(1).decode("utf-8")
        self.last_message = message
        return message

    def close(self) :
        self.sock.close()

if __name__ == "__main__":
    if len(sys.argv) != 3 :
        exit(84)
    server_manager = ServerManager(sys.argv[1], int(sys.argv[2]))
    print("Server manager")
    while(True) :
        print("starting receiving")
        server_message = server_manager.recv()
        print(server_message)
        server_manager.send("idn ia\n".encode(encoding="utf-8"))
        print("Finished receiving")


