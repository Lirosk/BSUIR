class IP:
    def __init__(self, source_ip: int, destination_ip: int):
        self.source_ip = source_ip
        self.destination_ip = destination_ip
        self.version: int = 4
        self.header_len: int = 0
        self.service_type: int = 0
        self.packet_size: int = 0
        self.datagram_id: int = 0
        self.flags: int = 0
        self.fragment_pointer: int = 0
        self.TTL: int = 0
        self.protocol: int = 6
        self.checksum: int = 0
        self.ip_parameters: int = 0
        self.data: int = 0

    def __repr__(self) -> str:
        return f'{{ source_ip = {self.source_ip}, destination_ip = {self.destination_ip} }}'
