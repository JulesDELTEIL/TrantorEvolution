##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## player.py
##

from motivation import Motivation

class PlayerState:
    def __init__(self):
        self.level = 1
        self.food = 10
        self.inventory = {}
        self.vision = []
        self.motivation = Motivation()
    
    def update(self, response):
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
        self.vision = response.strip("[]").split(",")
        