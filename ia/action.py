##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## action.py
##

from enum import Enum

class Action(Enum):
    FORWARD = "Forward"
    LEFT = "Left"
    RIGHT = "Right"
    LOOK = "Look"
    INVENTORY = "Inventory"
    BROADCAST = "Broadcast"
    TAKE = "Take"
    SET = "Set"
    FORK = "Fork"
    INCANTATION = "Incantation"
    CONNECT_NBR = "Connect_nbr"
    EJECT = "Eject"
    NONE = None
