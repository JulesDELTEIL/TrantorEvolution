##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## role_map.py
##

from src.roles.foreman import Foreman
from src.roles.worker import Worker
from src.roles.queen import Queen
from src.roles.kamikaze import Kamikaze
from src.roles.nobody import Nobody
from src.roles.matriarch import Matriarch

ROLE_MAP = {
    "Queen": Queen(),
    "First_Queen": Queen(True),
    "Foreman": Foreman(),
    "Matriarch": Matriarch(),
    "Worker": Worker(),
    "Kamikaze": Kamikaze(),
    "Nobody": Nobody()
}
