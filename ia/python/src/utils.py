##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## utils.py
##

from src.roles.role_map import ROLE_MAP

def recv_until_newline(sock):
    data = b""
    while not data.endswith(b"\n"):
        chunk = sock.recv(4096)
        if not chunk:
            raise ConnectionError("Disconnected")
        data += chunk
    return data.decode()
