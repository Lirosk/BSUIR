import ClientDB

from KeyDistributionCenter import KeyDistributionCenter
from Client import Client


def main():
    KDC = KeyDistributionCenter()

    client = ClientDB.clients[0]
    client.interact_with_server(KDC, "service_server_id")


if __name__ == '__main__':
    main()
    