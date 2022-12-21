import random

__created_keys = set()

def __generate_key() -> str:
    return str(random.randint(10_000_000, 99_999_999)) 

def create_key() -> str | None:
    while ((key := __generate_key()) not in __created_keys):
        __created_keys.add(key)
        return key
