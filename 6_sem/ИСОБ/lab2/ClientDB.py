import KeyCreator

from typing import *
from Client import Client

clients: List[Client] = []

for _ in range(3):
    clients.append(Client(KeyCreator.create_key(), KeyCreator.create_key()))

def have_client(client_id) -> bool:
    for client in clients:
        if client.id == client_id:
            return True

    return False

def get_client_key(client_id: str) -> str:
    for client in clients:
        if client.id == client_id:
            return client.key

    raise IndexError(client_id)