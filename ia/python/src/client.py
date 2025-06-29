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
    """
    Core of AI. Handle communication with server and the algo.
    """
    def __init__(self, host, port, team_name):
        ServerManager.__init__(self, host, port)
        Player.__init__(self, host, str(port), team_name)
        Communication.__init__(self, team_name, self._sock)
        self._host: str = host
        self._port: str = port
        self._team_name: str = team_name

    def main_loop(self) -> None:
        self.run()
