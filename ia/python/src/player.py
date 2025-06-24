##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## player.py
##

from src.motivation import Motivation
from src.action import *

class PlayerState:
    def __init__(self):
        self.level = 1
        self.food = 10
        self.egg_left = -1
        self.last_inventory = {}
        self.last_vision = []
        self.motivation = Motivation()
        self.sent_queue = []
    
    def update(self, response: str) -> None:
        #toutes ces conditions doivent être gérer via la sent_queue -> on doit regarder quel est le premier élément de la liste et traiter la réponse en fonction
        if response == "dead":
            print("I'm dead lol")
            exit(0)
        self.motivation.update(self.food, self.last_inventory, self.level)
    
    def parse_inventory(self, response: str) -> None:
        self.last_inventory = {}
        for item in response.strip("[]").split(","):
            if item.strip():
                key, val = item.strip().split()
                self.last_inventory[key] = int(val)
        self.food = self.last_inventory.get("food", 0)
        
    def parse_vision(self, response: str) -> list[list[str]]:
        s = response.strip()
        if not (s.startswith('[') and s.endswith(']')):
            raise ValueError("Format inattendu")
        inner = s[1:-1]

        raw_tiles = inner.split('],')
        vision = []
        for raw in raw_tiles:
            t = raw.strip()
            if t.startswith('['):
                t = t[1:]
            if t.endswith(']'):
                t = t[:-1]
            if t == '':
                vision.append([])
            else:
                parts = [w.strip() for w in t.split(' ') if w.strip()]
                vision.append([w.strip(',') for w in parts])
        return vision
    
    def get_movements(start: list[int], end: list[int], direction: str) -> list[Commands]:
        commands_queue = []
        dx = end[0] - start[0]
        dy = end[1] - start[1]

        directions = ['up', 'right', 'down', 'left']

        def turn_to(current, target):
            moves = []
            ci = directions.index(current)
            ti = directions.index(target)
            diff = (ti - ci) % 4
            if diff == 1:
                moves.append(Commands(Action.RIGHT))
            elif diff == 2:
                moves += [Commands(Action.RIGHT), Commands(Action.RIGHT)]
            elif diff == 3:
                moves.append(Commands(Action.LEFT))
            return moves

        # Mouvements en x
        if dx != 0:
            target_dir = 'right' if dx > 0 else 'left'
            commands_queue += turn_to(direction, target_dir)
            commands_queue += [Commands(Action.FORWARD)] * abs(dx)
            direction = target_dir

        # Mouvements en y
        if dy != 0:
            target_dir = 'up' if dy > 0 else 'down'
            commands_queue += turn_to(direction, target_dir)
            commands_queue += [Commands(Action.FORWARD)] * abs(dy)
            direction = target_dir

        return commands_queue
