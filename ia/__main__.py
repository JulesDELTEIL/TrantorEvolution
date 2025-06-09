#!/usr/bin/env python3
#
## EPITECH PROJECT, 2025
## TrantorEvolution
## File description:
## IA CLIENT MAIN
#

from client import Trantorian

if __name__ == "__main__":
    client = Trantorian(host="localhost", port=8000, team_name="team")
    client.run()