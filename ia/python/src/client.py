##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## client.py
##

from src.communication import Communication
from src.server_manager import ServerManager
from src.player import Player

class Trantorian(ServerManager, Player, Communication):
    def __init__(self, host, port, team_name):
        ServerManager.__init__(self, host, port)
        Player.__init__(self, host, str(port), team_name)
        Communication.__init__(self, team_name, self._sock)
        self._host = host
        self._port = port
        self._team_name = team_name

    def main_loop(self) -> None:
        self.run()
