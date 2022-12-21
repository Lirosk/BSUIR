from __future__ import annotations
from threading import Thread
from typing import List
from time import sleep

from IP import IP
from TCP import TCP

class Connection:
    def __init__(self, clients: List[Client]):
        self.clients = clients

    def send(self, tcp: TCP) -> None:
        if tcp is None:
            self._close()
            return

        receiver = self._find_receiver(tcp)
        if not receiver.connected:

            return

        receiver.receive(tcp)

    def add_client(self, client: Client) -> None:
        self.clients.append(client)

    def _close(self):
        for client in self.clients:
            client.close()

    def _find_receiver(self, tcp: TCP) -> Client:
        for client in self.clients:
            if (tcp.ip.destination_ip, tcp.destination_port) == (client.ip, client.port):
                return client
        
        return None


SLEEP_TIME_SECONDS = 2

class Client:
    def __init__(self, ip: int, port: int, connection: Connection):
        self.ip = ip
        self.port = port

        self.connected = True
        self.connection = connection

        self.TCP_buffer: List[TCP] = []

        self._first_data_to_send = 9

        self.buffer_processer = Thread(target=self._process_buffer)
        self.buffer_processer.start()


    def start_communicating(self) -> None:
        receiver = self.connection.clients[1]

        tcp = self._build_package(receiver)
        self.send(tcp)

    def send(self, tcp: TCP) -> None:
        if not self.connected:
            return

        print(f'{self.ip}:{self.port} sending tcp package:\n{tcp}.')
        self.connection.send(tcp)

    def receive(self, tcp_received: TCP) -> None:
        if not self.connected:
            return

        print(f'{self.ip}:{self.port} received tcp package:\n{tcp_received}.\n')
        self.TCP_buffer.append(tcp_received)

    def close(self):
        self.connected = False
        print(f'{self.ip}:{self.port} closed connection.\n')
        self.TCP_buffer = []

    def _process_buffer(self) -> None:
        while self.connected:
            while len(self.TCP_buffer) != 0:
                tcp_received = self.TCP_buffer.pop(0)
                if tcp_received.RST:
                    print(f"\n{self.ip}:{self.port} received tcp package with RST flag.\n")
                    self.connection._close()
                    break

                tcp_answer = self._build_answer(tcp_received)
                self.send(tcp_answer)
                sleep(SLEEP_TIME_SECONDS)

    def _build_answer(self, tcp_received: TCP) -> TCP:
        ip = IP(tcp_received.ip.destination_ip, tcp_received.ip.source_ip)
        tcp = TCP(ip, tcp_received.destination_port, tcp_received.source_port)

        tcp.ACK = 1
        tcp.SN = tcp_received.AN
        tcp.AN = tcp_received.SN + 1

        data_received = tcp_received.data
        tcp.data = (data_received * 3 + 1) if (data_received % 2) else (data_received // 2)

        return tcp

    def _build_package(self, receiver: Client) -> TCP:
        ip = IP(self.ip, receiver.ip)
        tcp = TCP(ip, self.port, receiver.port)

        tcp.ACK = 1
        tcp.SN = 0
        tcp.AN = 1

        tcp.data = self._first_data_to_send
        self._first_data_to_send += 1

        return tcp


class Attacker(Client):
    def __init__(self, ip: int, port: int, connection: Connection):
        super().__init__(ip, port, connection)
        self.victims = connection.clients[:2]
        self._start_attacking()

    def _start_attacking(self):
        for victim in self.victims:
            Thread(target=self._start_RST_attack_on_client, args=(victim,), daemon=True).start()

    def _start_RST_attack_on_client(self, client: Client):
        while self.connected and client.connection:
            while len(client.TCP_buffer) > 0 :
                last_tcp_received = client.TCP_buffer[-1]

                tcp_answer = self._build_answer(last_tcp_received)
                tcp_answer.ip.source_ip = client.ip
                tcp_answer.source_port = client.port

                self.send(tcp_answer)

                sleep(SLEEP_TIME_SECONDS)

    def _build_answer(self, tcp_received: TCP) -> TCP:
        tcp_answer = super()._build_answer(tcp_received)
        tcp_answer.data = 0
        tcp_answer.RST = 1
        return tcp_answer
