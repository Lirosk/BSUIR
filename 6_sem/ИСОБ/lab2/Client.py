from datetime import datetime
import Des

from KeyDistributionCenter import KeyDistributionCenter

class Client:
    def __init__(self, client_id: str, client_key: str):
        self.id: str = client_id
        self.key: str = client_key

    def interact_with_server(self, KDC: KeyDistributionCenter, service_server_id: str):
        TGT_K_AS_TGS, K_C_TGS = self.__get_TGT(KDC)
        TGS_K_TGS_SS, K_C_SS = self.__get_TGS(KDC, TGT_K_AS_TGS, K_C_TGS, service_server_id)
        t4, response = self.__send_ticket_to_SS(KDC, TGS_K_TGS_SS, K_C_SS)

        print()
        if t4 + 1 == float(response):
            print("Клиент установил соединение с сервером.")
        else:
            print("Метка времени из аутентификационного блока не совпадает.")

        print()

    def __get_TGT(self, KDC: KeyDistributionCenter):
        message = (self.id,)
        print(f"Клиент начинает общение с AS, сообщение:\n{message}\n")

        response_K_C = KDC.AS.get_TGT(*message)
        print(f"Клиент получает ответ от AS, зашифрованный ответ:\n{response_K_C}")
        _TGT, *_ = response_K_C

        TGT_K_AS_TGS, K_C_TGS = Des.decrypt(self.key, response_K_C)
        print(f"Расшифрованный ответ ключом K_C = {self.key}:\n{(TGT_K_AS_TGS, K_C_TGS)}\n")

        return TGT_K_AS_TGS, K_C_TGS

    def __get_TGS(self, KDC: KeyDistributionCenter, TGT_K_AS_TGS, K_C_TGS, service_server_id):
        t2 = datetime.now().timestamp()
        AUT1 = (self.id, t2)
        AUT1_K_C_TGS = Des.encrypt(K_C_TGS, AUT1)
        ID = service_server_id

        message = (TGT_K_AS_TGS, AUT1, ID)
        print(f"Сообщение клиента для TGS:\n{message}")

        message_encrypted = (TGT_K_AS_TGS, AUT1_K_C_TGS, ID)
        print(f"Зашифрованный AUT1:\n{{{AUT1_K_C_TGS}}}{K_C_TGS}")

        print(f"Клиент отправляет сообщение TGS:\n{message_encrypted}\n\n")
        response_K_C_TGS = KDC.TGS.get_TGS(*message_encrypted)
        print(f"Клиент получил ответ:\n{response_K_C_TGS}")
        _TGS, *_ = response_K_C_TGS

        response = Des.decrypt(K_C_TGS, response_K_C_TGS)
        print(f"Расшифрованный ответ:\n{response}\n\n")
        _TGS, *_ = response

        return response

    def __send_ticket_to_SS(self, KDC: KeyDistributionCenter, TGS_K_TGS_SS, K_C_SS):
        t4 = datetime.now().timestamp()
        AUT2 = (self.id, t4)
        AUT2_K_C_SS = Des.encrypt(K_C_SS, AUT2)

        message = (TGS_K_TGS_SS, AUT2)
        print(f"Сообщение клиента для SS:\n{message}")

        message_encrypted= (TGS_K_TGS_SS, AUT2_K_C_SS)
        print(f"Зашифрованный AUT2:\n{{{AUT2_K_C_SS}}}{K_C_SS}")

        print(f"Клиент отправляет сообщение SS:\n{message_encrypted}\n\n")
        response_K_C_SS = KDC.SS.connect(*message_encrypted)
        print(f"Клиент получает ответ от SS:\n{response_K_C_SS}")

        response = Des.decrypt(K_C_SS, response_K_C_SS)
        print(f"Расшифрованный ответ ключом {K_C_SS = }:\n{response}")

        return t4, response
        