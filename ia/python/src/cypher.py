##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## action.py
##
import base64

import cryptography
from cryptography.fernet import Fernet

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
