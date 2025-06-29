##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## map_memory.py
##

class MapMemory:
    def __init__(self, decay: float = 0.1):
        self._tiles: dict[str, dict[str, any]] = {}
        self._decay: float = decay  # perte de confiance par cycle

    def update_mindmap(self, response_formatted: list[list[str]], level: int, cycle: int, pos: list[int]) -> None:
        relative_coords = self._vision_coords(level)
        px, py = pos[0], pos[1]
        for i in range(len(relative_coords)):
            absolute_coord = [px + relative_coords[i][0], py + relative_coords[i][1]]
            self._update(absolute_coord, response_formatted[i], cycle)

    def _update(self, coord: list[int], objects: list[str], cycle: int) -> None:
        self._tiles[coord.__str__()] = {'last_seen': cycle, 'objects': objects}

    def trust(self, coord: list[int], cycle: int) -> float:
        entry = self._tiles.get(coord.__str__())
        if not entry:
            return 0.0
        age = cycle - entry['last_seen']
        return max(0.0, 1.0 - age * self._decay)
    
    def _vision_coords(self, level: int) -> list[list[int]]:
        coords = []
        coords.append([0, 0])
        for r in range(1, level + 1):
            y = r
            for x in range(-r, r + 1):
                coords.append([x, y])
        return coords
