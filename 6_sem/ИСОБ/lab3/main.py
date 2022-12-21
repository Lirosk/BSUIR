from time import sleep
from Models import *

def main():
    connection = Connection([])
    client1 = Client(1, 1, connection)
    client2 = Client(2, 2, connection)

    connection.add_client(client1)
    connection.add_client(client2)

    client1.start_communicating()

    sleep(5)
    connection.add_client(Attacker(3, 3, connection))
    
        
if __name__ == '__main__':
    main()
    