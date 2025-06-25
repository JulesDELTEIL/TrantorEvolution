##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## worker.py
##

from src.roles.base_role import BaseRole
from src.action import Commands, Action
from src.stones import STONES

class Worker(BaseRole):
    def __init__(self):
        super().__init__()
        print("----- Je suis Worker ------")
        self.mode = 'GATHERING' # GATHERING or DELIVERING
        self.carry = None
        #self.queens_pos = None
        
        #test
        self.queens_pos = [0, 0]
        self.direction = "up"
        
    def decide_action(self) -> None:
        self.cycle += 1
        # if self.state.motivation.hunger > 0.7:
            # logique pour chercher de la food (vision...)
        if self.mode == 'GATHERING':
            print("condition")
            print(self.state.last_vision)
            for objects in self.state.last_vision:
                for stone in STONES.keys():
                    if stone in objects:
                        self.carry = stone
                        self.mode = 'DELIVERING'
                        self.queue.appendleft(Commands(Action.TAKE, stone))
                        return
            
            self.queue.appendleft(Commands(Action.FORWARD))
            if self.cycle % 2 == 0:
                self.queue.appendleft(Commands(Action.LEFT))
            else:
                self.queue.appendleft(Commands(Action.RIGHT))
            self.queue.appendleft(Commands(Action.FORWARD))
            self.queue.appendleft(Commands(Action.LOOK))
            return

        elif self.mode == 'DELIVERING':
            if self.pos == self.queens_pos:
                print("je pose", self.carry)
                self.mode = 'GATHERING'
                self.queue.appendleft(Commands(Action.SET, self.carry))
                self.carry = None
            else:
                self.state.get_movements(self.pos, self.queens_pos, self.direction)
    
    def setup_direction(self) -> None:
        self.queue.appendleft(Commands(Action.FORWARD))

    def handle_broadcast(self, response_list: list[str]) -> bool:
        #if self.direction is None:
        #    if response_list[1][0] != "0" and response_list[2] == "here":
        #        if response_list[1][0] == "1":
        #            self.queue.appendleft(Commands(Action.LEFT))
        #            self.queue.appendleft(Commands(Action.LEFT))
        #            self.queens_pos = [0, -2]
        #        if response_list[1][0] == "3":
        #            self.queue.appendleft(Commands(Action.RIGHT))
        #            self.queens_pos = [1, -3]
        #        if response_list[1][0] == "7":
        #            self.queue.appendleft(Commands(Action.RIGHT))
        #            self.queens_pos = [-1, -3]
        #        self.direction = "up"
        #        return True
        return False