##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## utils.py
##

import re
from collections import deque
from src.action import Commands, Action

def parse_vision(response: str) -> list[list[str]]:
    s = response.strip()
    if not (s.startswith('[') and s.endswith(']')):
        raise ValueError("Format inattendu")
    inner = s[1:-1]

    raw_tiles = inner.split(',')
    vision = []
    for raw in raw_tiles:
        raw = raw.strip()
        if raw == '':
            vision.append([])
        else:
            objs = [obj for obj in raw.split() if obj]
            vision.append(objs)
    return vision

def parse_inventory(response: str) -> dict:
    pairs = re.findall(r'(\w+)\s+(\d+)', response)
    inventory = {key: int(val) for key, val in pairs}
    return inventory

def get_movements(start: list[int], end: list[int], direction: str) -> list[Commands]:
    commands_queue = deque()
    dx = end[0] - start[0]
    dy = end[1] - start[1]

    directions = ['up', 'right', 'down', 'left']

    def turn_to(current, target, queue):
        ci = directions.index(current) + 1
        ti = directions.index(target) + 1
        diff = (ti - ci) % 4
        if diff == 1:
            queue.appendleft(Commands(Action.LEFT))
        elif diff == 2:
            queue.appendleft(Commands(Action.RIGHT))
            queue.appendleft(Commands(Action.RIGHT))
        elif diff == 3:
            queue.appendleft(Commands(Action.RIGHT))
        return queue

    if dx != 0:
        target_dir = 'right' if dx > 0 else 'left'
        turn_to(direction, target_dir, commands_queue)
        for _ in range(abs(dx)):
            commands_queue.appendleft(Commands(Action.FORWARD))
        direction = target_dir

    if dy != 0:
        target_dir = 'up' if dy > 0 else 'down'
        turn_to(direction, target_dir, commands_queue)
        for _ in range(abs(dy)):
            commands_queue.appendleft(Commands(Action.FORWARD))
        direction = target_dir
    return commands_queue
