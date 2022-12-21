import KeyCreator

class KeyDistributionCenter:
    ticket_TTL: str = str(10*60)

    def __init__(self):
        from AuthenticationServer import AuthenticationServer
        from TicketGrantingServer import TicketGrantingServer
        from ServiceServer import ServiceServer

        self.AS = AuthenticationServer(self)
        self.TGS = TicketGrantingServer(self)
        self.SS = ServiceServer(self)

        self.K_C_TGS = KeyCreator.create_key()
        self.K_AS_TGS = KeyCreator.create_key()
        self.K_C_TGT = KeyCreator.create_key()
        self.server_id = KeyCreator.create_key()
        self.K_C_SS = KeyCreator.create_key()
        self.K_TGS_SS = KeyCreator.create_key()

    def get_TGS_id(self) -> str:
        return str(0)
