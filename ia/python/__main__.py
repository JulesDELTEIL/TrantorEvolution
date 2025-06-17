#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## IA CLIENT MAIN
#
import sys
from src.client import Trantorian

ARG_NB = 7
ERROR = 84


def create_configuration():
    conf = {
        "-h": "",
        "-n": "",
        "-p": ""
    }
    if len(sys.argv) < ARG_NB:
        raise Exception("Too few arguments")
    for i in range(1, ARG_NB - 1, 2) :
        if not sys.argv[i] in conf.keys() :
            raise Exception("Flag mismatch")
        conf[sys.argv[i]] = sys.argv[i + 1]
    if not conf["-p"].isdigit() :
        raise Exception("Port number is not a number")
    if conf["-n"] == "GRAPHIC" :
        raise Exception("Team name cant be 'GRAPHIC'")
    return conf

if __name__ == "__main__":
    conf = create_configuration()
    client = Trantorian(conf["-h"], int(conf["-p"]), conf["-n"])
    client.run()
