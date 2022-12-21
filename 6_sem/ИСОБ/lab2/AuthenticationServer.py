import ClientDB
import Des

from datetime import datetime

class AuthenticationServer:
    from KeyDistributionCenter import KeyDistributionCenter
    def __init__(self, KDC: KeyDistributionCenter):
        self.KDC = KDC

    def get_TGT(self, client_id: str):
        print(f"AS получил сообщение от клиента, сообщение:\n{client_id}")

        if ClientDB.have_client(client_id):
            print("Клиент есть в базe")

            client_key = ClientDB.get_client_key(client_id)
            print(f"AS получает K_C = {client_key}\n")

            TGT = self.__create_TGT(client_id)
            print(f"AS сформировал TGT:\n{TGT}")

            *_, K_C_TGS = TGT

            TGT_K_AS_TGS = Des.encrypt(self.KDC.K_AS_TGS, TGT)
            print(f"Зашифрованный TGT:\n{{{TGT_K_AS_TGS}}}{self.KDC.K_AS_TGS}\n")

            response = (TGT_K_AS_TGS, K_C_TGS)
            print(f"Ответ для клиента:\n{response}")

            response_K_C = Des.encrypt(client_key, response)
            print(f"Зашифрованный ответ для клиента:\n{{{response_K_C}}}{client_key}")

            print(f"AS отправляет ответ для клиента:\n{response_K_C}\n\n")
            return response_K_C
        else:
            print("Пользователя с данным идентификатором нет в базе")
            exit(0)

    def __create_TGT(self, client_id: str):
        K_C_TGS = self.KDC.K_C_TGS 

        TGS_id = self.KDC.get_TGS_id()
        p1 = datetime.now().timestamp()
        t1 = self.KDC.ticket_TTL

        TGT = (
            client_id,
            TGS_id,
            t1,
            p1,
            K_C_TGS,
        )
        
        return TGT