from IP import IP

class TCP:
    def __init__(self, ip: IP, source_port: int, destination_port: int):
        self.ip = ip
        self.source_port = source_port
        self.destination_port = destination_port
        self.SN: int = 0
        self.AN: int = 0
        self.header_len: int = 0
        self.reserved: int = 0
        self.URG: int = 0
        self.ACK: int = 0
        self.PSH: int = 0
        self.RST: int = 0
        self.SYN: int = 0
        self.FIN: int = 0
        self.window_size: int = 0
        self.checksum: int = 0
        self.urgent: int = 0
        self.data: int = 0

    def __repr__(self) -> str:
        return f"{{ ip = {self.ip}, source_port = {self.source_port}, destination_port = {self.destination_port}, ACK = {self.ACK}, RST = {self.RST} SN = {self.SN}, AN = {self.AN}, data = {self.data} }}"
