##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## action.py
##
import base64

import cryptography
from cryptography.fernet import Fernet
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
import os
import sys

def create_key(code: str) -> Fernet:
    code_bytes = code.encode("utf-8")
    key = base64.urlsafe_b64encode(code_bytes.ljust(32)[:32])
    f = Fernet(key)
    return f

def cypher(message: str, key: str):
   f = create_key(key)
   return f.encrypt(message.encode(encoding="utf-8")).decode("utf-8")


def decypher(message: str, key: str):
    f = create_key(key)
    try:
        return f.decrypt(bytes(message, "utf-8")).decode("utf-8")
    except cryptography.fernet.InvalidToken:
        return None

def main():
    print(sys.argv)
    if len(sys.argv) != 4:
        raise Exception("Invalid number of arguments")
    print(sys.argv[3])
    if sys.argv[3] == 'cypher':
        print(str(cypher(sys.argv[1], sys.argv[2])))
    if sys.argv[3] == 'decypher':
        print(decypher(sys.argv[1], sys.argv[2]))

if __name__ == '__main__':
    main()

