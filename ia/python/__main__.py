#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## IA CLIENT MAIN
#
import sys
import socket
from src.client import Trantorian

MIN_ARG_NB = 5
MAX_ARG_NB = 7
ERROR = 84

def create_configuration():
    conf = {
        "-h": "",
        "-n": "",
        "-p": ""
    }
    len_arg = len(sys.argv)
    if len_arg != MIN_ARG_NB and len_arg != MAX_ARG_NB:
        raise ValueError("USAGE: ./zappy_ai -p port -n team_name [-h ip]")
    for i in range(1, len_arg - 1, 2):
        if not sys.argv[i] in conf.keys():
            raise NameError("Flag mismatch")
        conf[sys.argv[i]] = sys.argv[i + 1]
    if not conf["-p"].isdigit() or int(conf["-p"]) < 1025 or int(conf["-p"]) > 65535:
        raise ValueError("Port number must be between 1025 and 65535 includes")
    if conf["-n"] == "GRAPHIC":
        raise NameError("Team name can't be 'GRAPHIC'")
    if not conf["-h"]:
        conf["-h"] = "127.0.0.1"
    return conf

if __name__ == "__main__":
    try :
        conf = create_configuration()
        client = Trantorian(conf["-h"], int(conf["-p"]), conf["-n"])
        client.main_loop()
    except (ValueError, NameError, ConnectionRefusedError, ConnectionError, ConnectionResetError) as e :
        print("Error :", e, file=sys.stderr)


