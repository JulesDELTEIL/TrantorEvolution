#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## Server Manager
#

import socket

BUFF_SIZE = 1024

class ServerManager:
    def __init__(self, host: str, port: int):
        self._host = host
        self._port = port
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._sock.connect((self._host, self._port))

    def send(self, message):
        self._sock.send(message)

    def recv(self):
        message = ""
        while not "\n" in message:
            self._sock.setblocking(True)
            data = self._sock.recv(BUFF_SIZE)
            self._sock.setblocking(False)
            while True:
                try:
                    if not data:
                        break
                    message += data.decode("utf-8")
                    data = self._sock.recv(BUFF_SIZE)
                except BlockingIOError:
                    break
            if not data:
                return None
        return message

    def close(self):
        self._sock.close()
