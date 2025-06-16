##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## player.py
##

from src.motivation import Motivation

class PlayerState:
    def __init__(self):
        self.level = 1
        self.food = 10
        self.inventory = {}
        self.vision = []
        self.motivation = Motivation()
        self.sent_queue = []
    
    def update(self, response):
        #toutes ces conditions doivent être gérer via la sent_queue -> on doit regarder quel est le premier élément de la liste et traiter la réponse en fonction
        if response.startswith("[") and "food" in response:
            self.parse_inventory(response)
        elif response.startswith("[") and "player" in response:
            self.parse_vision(response)
        elif response == "dead":
            print("I'm dead lol")
            exit(0)
        self.motivation.update(self.food, self.inventory, self.level)
    
    def parse_inventory(self, response):
        self.inventory = {}
        for item in response.strip("[]").split(","):
            if item.strip():
                key, val = item.strip().split()
                self.inventory[key] = int(val)
        self.food = self.inventory.get("food", 0)
        
    def parse_vision(self, response):
        content = response.strip("[]")
        tiles = content.split(",")
        self.vision = [tile.strip().split() for tile in tiles]
        
    def vision_coords(level):
        coords = [(0, 0)]
        for r in range(1, level + 1):
            y = -r
            for x in range(-r, r + 1):
                coords.append((x, y))
        return coords
        