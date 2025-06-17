#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## Server Manager
#

import socket
from collections import deque
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
        while not "\n" in message :
            self.sock.setblocking(True)
            data = self.sock.recv(BUFF_SIZE)
            self.sock.setblocking(False)
            while True :
                try :
                    if not data :
                        break
                    message += data.decode("utf-8")
                    data = self.sock.recv(BUFF_SIZE)
                except BlockingIOError :
                    break
            if not data :
                return None
        return message

    def close(self) :
        self.sock.close()

if __name__ == "__main__":
    server_message = ""
    if len(sys.argv) != 3 :
        exit(84)
    server_manager = ServerManager(sys.argv[1], int(sys.argv[2]))
    print("Server manager")
    while(True) :
        print("Starting receiving")
        server_message += server_manager.recv()
        if not server_message:
            exit(84)
        print("Receiving :", server_message)
        while server_message :
            index = server_message.find("\n")
            if index == -1:
                break
            print("Index :", index)
            print("MESSAGE :", server_message[:index + 1])
            print("FROM SOURCE", server_message)
            server_message = server_message[index + 1:]
        print("Finished receiving with [", server_message, "] Left\n")


