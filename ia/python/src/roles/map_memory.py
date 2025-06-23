##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## map_memory.py
##

class MapMemory:
    def __init__(self, decay: float = 0.1):
        self.tiles: dict[list[int], list[str]] = {}
        self.decay = decay  # perte de confiance par cycle

    def update_mindmap(self, response_formatted: list[list[str]], level: int, cycle: int, pos: list[int]) -> None:
        relative_coords = self._vision_coords(level)
        px, py = pos[0], pos[1]
        for (dx, dy), objects in zip(relative_coords, response_formatted):
            absolute_coord = [px + dx, py + dy]
            self.update(absolute_coord, objects, cycle)

    def update(self, coord: list[int], objects: list[str], cycle: int) -> None:
        self.tiles[coord] = {'last_seen': cycle, 'objects': objects}

    def trust(self, coord: list[int], cycle: int) -> float:
        entry = self.tiles.get(coord)
        if not entry:
            return 0.0
        age = cycle - entry['last_seen']
        return max(0.0, 1.0 - age * self.decay)
    
    def _vision_coords(level: int) -> list[list[int]]:
        coords = [0, 0]
        for r in range(1, level + 1):
            y = -r
            for x in range(-r, r + 1):
                coords.append([x, y])
        return coords
