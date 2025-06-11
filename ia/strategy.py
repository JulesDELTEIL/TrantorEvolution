##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## strategy.py
##

from action import Action

def decide_next_action(player):
    hunger = player.motivation.hunger
    evolve = player.motivation.evolution
    
    if hunger > 0.7:
        if "food" in player.vision:
            return Action.TAKE
        return Action.LOOK

    if evolve > 0.6:
        return Action.INCANTATION
    return Action.LOOK
