##
## EPITECH PROJECT, 2024
## TrantorEvolution
## File description:
## action.py
##

import base64
import cryptography
from cryptography.fernet import Fernet
import random

ROCKYOU_PATH = "rockyou.txt"

def create_key(code: str) -> Fernet:
    code_bytes = code.encode("utf-8")
    key = base64.urlsafe_b64encode(code_bytes.ljust(32, b'\0')[:32])
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
    
def open_rockyou_file(filepath: str = ROCKYOU_PATH) -> list[str] | None:
    try:
        with open(filepath, "r", encoding="utf-8") as file:
            words = [line.strip() for line in file if line.strip()]
    except FileNotFoundError:
        return None
    if not words:
        return None
    else:
        return words

def crack_fernet(message: str, wordlist: str, sample_size: int = 50) -> str | None:
    words = random.sample(wordlist, min(sample_size, len(wordlist)))
    for word in words:
        if decypher(message, word) is not None:
            return word
    return None
