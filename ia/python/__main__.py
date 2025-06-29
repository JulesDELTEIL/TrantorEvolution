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
    if len(sys.argv) != ARG_NB:
        raise Exception("USAGE: ./zappy_ai -p port -h ip -n team_name")
    for i in range(1, ARG_NB - 1, 2):
        if not sys.argv[i] in conf.keys():
            raise Exception("Flag mismatch")
        conf[sys.argv[i]] = sys.argv[i + 1]
    if not conf["-p"].isdigit() or int(conf["-p"]) < 1025 or int(conf["-p"]) > 65535:
        raise Exception("Port number must be between 1025 and 65535 includes")
    if conf["-n"] == "GRAPHIC":
        raise Exception("Team name can't be 'GRAPHIC'")
    return conf

if __name__ == "__main__":
    conf = create_configuration()
    client = Trantorian(conf["-h"], int(conf["-p"]), conf["-n"])
    client.main_loop()
