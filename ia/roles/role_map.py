##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## role_map.py
##

from roles.foreman import Foreman
from roles.worker import Worker
from roles.queen import Queen
from roles.kamikaze import Kamikaze
from roles.matriarch import Matriarch

ROLE_MAP = {
    "Queen": Queen(),
    "Foreman": Foreman(),
    "Matriarch": Matriarch(),
    "Worker": Worker(),
    "Kamikaze": Kamikaze()
}
