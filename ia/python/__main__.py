#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## IA CLIENT MAIN
#
import sys
from src.client import Trantorian

PORT = 2
HOST_NAME = 4
TEAM_NAME = 6
ARG_NB = 7
ERROR = 84

def main_error_handling():
    flag_list = ["-p", "-n", "-h"]
    if len(sys.argv) < ARG_NB:
        raise Exception("Too few arguments")
    j = 0
    for i in range(1, ARG_NB - 1, 2) :
        if sys.argv[i] != flag_list[j] :
            raise Exception("Flag mismatch")
        j += 1
    if not sys.argv[PORT].isdigit() :
        raise Exception("Port number is not a number")
    if sys.argv[TEAM_NAME] == "GRAPHIC" :
        raise Exception("Team name cant be 'GRAPHIC'")



if __name__ == "__main__":
    print("hello world")
    print(len(sys.argv))
    print(*sys.argv)
    main_error_handling()
    client = Trantorian(sys.argv[HOST_NAME], sys.argv[PORT], sys.argv[TEAM_NAME])
    client.run()
