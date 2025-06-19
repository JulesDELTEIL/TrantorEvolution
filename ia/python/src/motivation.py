##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## motivation.py
##

class Motivation:
    def __init__(self):
        self.hunger = 0.0 # 1 = hungry
        self.evolution = 0.0 # 1 = want to evolve
        self.last_food = 10
    
    def update(self, food_remaining, inventory, level):
        self.hunger = min(1.0, max(0.0, 1 - food_remaining / 10))
        self.evolution = self._compute_evolution_score(inventory, level)
        
    def _compute_evolution_score(self, inventory, level):
        requirements = Motivation.LEVEL_REQUIREMENTS.get(level)
        if not requirements:
            return 0.0
        #total_required = sum(requirements.values)
        total_met = 0
        
        for stone, quantity_needed in requirements.items():
            quantity_have = inventory.get(stone, 0)
            total_met += min(quantity_have, quantity_needed)
        
        return total_met #/ total_required
    
    LEVEL_REQUIREMENTS = {
        1: {"linemate": 1},
        2: {"linemate": 1, "deraumere": 1, "sibur": 1},
        3: {"linemate": 2, "sibur": 1, "phiras": 1},
        4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
        5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
        6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
        7: {"linemate": 2, "deraumere": 2, "sibur": 2, "phiras": 2, "thystame": 1},
    }