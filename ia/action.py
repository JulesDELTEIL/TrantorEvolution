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
    TAKE = "Take object"
    SET = "Set object"
    FORK = "Fork"
    INCANTATION = "Incantation"
    CONNECT_NBR = "Connect_nbr"
    EJECT = "Eject"
    NONE = None

class Commands:
    def __init__(self, action: Action, argument: str = None):
        self.action = action
        self.argument = argument
        
    def __str__(self):
        if self.argument:
            return f"{self.action.value} {self.argument}"
        return self.action.value

    COMMANDS = {
        Action.FORWARD: {"time": 7, "response success": ["ok"], "response error": ""},
        Action.LEFT: {"time": 7, "response success": ["ok"], "response error": ""},
        Action.RIGHT: {"time": 7, "response success": ["ok"], "response error": ""},
        Action.LOOK: {"time": 7, "response success": ["list_tile"], "response error": ""},
        Action.INVENTORY: {"time": 1, "response success": ["list_rock"], "response error": ""},
        Action.BROADCAST: {"time": 7, "response success": ["ok"], "response error": ""},
        Action.TAKE: {"time": 7, "response success": ["ok"], "response error": "ko"},
        Action.SET: {"time": 7, "response success": ["ok"], "response error": "ko"},
        Action.FORK: {"time": 42, "response success": ["ok"], "response error": ""},
        Action.INCANTATION: {"time": 300, "response success": ["Elevation underway", "Current level: "], "response error": "ko"},
        Action.CONNECT_NBR: {"time:": 0, "response success": ["value"]},
        Action.EJECT: {"time": 7, "response success": ["ok"], "response error": "ko"}
    }
    
