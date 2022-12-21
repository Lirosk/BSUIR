import Des

from datetime import datetime

class TicketGrantingServer:
    from KeyDistributionCenter import KeyDistributionCenter
    def __init__(self, KDC: KeyDistributionCenter):
        self.KDC = KDC

    def get_TGS(self, TGT_K_AS_TGS, AUT1_K_C_TSG, ID):
        print(f"TGS получает сообщение от клиента:\n{(TGT_K_AS_TGS, AUT1_K_C_TSG, ID)}\n")

        TGT = Des.decrypt(self.KDC.K_AS_TGS, TGT_K_AS_TGS)
        client_id_1, TGS_id, p1, t1, K_C_TGS = TGT
        print(f"TGS расшифровывает TGT ключом K_AS_TGS = {self.KDC.K_AS_TGS}:\n{TGT}")
        
        AUT1 = Des.decrypt(K_C_TGS, AUT1_K_C_TSG)
        client_id_2, t2 = AUT1
        print(f"TGS расшифровывает AUT1 ключом {K_C_TGS = }:\n{AUT1}")

        print(f"Расшифрованное сообщение:\n{(TGT, AUT1, ID)}\n")

        if (client_id_1 != client_id_2):
            print("Метка в блоке не совпадает с меткой в билете!")
            exit(0)
        else:
            print("Метка в блоке совпадает с меткой в билете")

        t1 = float(t1)
        t2 = float(t2)
        p1 = float(p1)

        if t2 - t1 > p1:
            print("Период дейтсвия билета истек!")
            exit(0)
        else:
            print("Билет действителен\n")

        TGS = self.__create_TGS(client_id_1)
        print(f"TGS сформировал TGS:\n{TGS}")

        TGS_K_TGS_SS = Des.encrypt(self.KDC.K_TGS_SS, TGS)
        print(f"Зашифрованный TGS:\n{{{TGS_K_TGS_SS}}}{self.KDC.K_TGS_SS}\n")

        K_C_SS = self.KDC.K_C_SS

        response = (TGS_K_TGS_SS, K_C_SS)
        print(f"Ответ TGS для клиента:\n{response}")

        response_K_C_TGS = Des.encrypt(K_C_TGS, response)
        print(f"Зашифрованный ответ для клиента:\n{{{response_K_C_TGS}}}{K_C_TGS}")
        _TGS, *_ = response_K_C_TGS

        print(f"TGS отправляет ответ клиенту:\n{response_K_C_TGS}\n\n")
        return response_K_C_TGS

    
    def __create_TGS(self, client_id: str):
        K_C_SS = self.KDC.K_C_SS
        server_id = self.KDC.server_id

        t3 = datetime.now().timestamp()
        p2 = self.KDC.ticket_TTL

        TGS = (
            client_id,
            server_id,
            t3,
            p2,
            K_C_SS
        )

        return TGS