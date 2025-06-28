##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## stones.py
##

X = 0
Y = 1

STONES = ['thystame', 'phiras', 'mendiane', 'sibur', 'deraumere', 'linemate']

LEVEL_REQUIREMENTS = {
    1: {"linemate": 1},
    2: {"linemate": 1, "deraumere": 1, "sibur": 1},
    3: {"linemate": 2, "sibur": 1, "phiras": 1},
    4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
    5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
    6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
    7: {"linemate": 2, "deraumere": 2, "sibur": 2, "phiras": 2, "thystame": 1},
}
