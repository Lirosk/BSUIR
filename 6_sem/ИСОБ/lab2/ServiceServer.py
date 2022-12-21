import Des

from KeyDistributionCenter import KeyDistributionCenter

class ServiceServer:
    def __init__(self, KDC: KeyDistributionCenter):
        self.KDC = KDC

    def connect(self, TGS_K_TGS_SS, AUT2_K_C_SS):
        print(f"SS получает сообщение от клиента: {(TGS_K_TGS_SS, AUT2_K_C_SS)}\n")

        TGS = Des.decrypt(self.KDC.K_TGS_SS, TGS_K_TGS_SS)
        print(f"SS расшифровывает TGS ключом K_TGS_SS = {self.KDC.K_TGS_SS}: {TGS}")

        AUT2 = Des.decrypt(self.KDC.K_C_SS, AUT2_K_C_SS)
        print(f"SS расшифровывает AUT2 ключом K_C_SS = {self.KDC.K_C_SS}: {AUT2}\n")

        client_id_1, server_id, t3, p2, K_C_SS = TGS
        client_id_2, t4 = AUT2

        if (client_id_1 != client_id_2):
            print("Метка в блоке не совпадает с меткой в билете!")
            exit(0)
        else:
            print("Метка в блоке совпадает с меткой в билете")

        t3 = float(t3)
        t4 = float(t4)
        p2 = float(p2)

        if t4 - t3 > p2:
            print("Период дейтсвия билета истек!")
            exit(0)
        else:
            print("Билет действителен\n")

        response = t4 + 1
        print(f"Сообщение SS для клиента: {response}")

        response_K_C_SS = Des.encrypt(K_C_SS, response)
        print(f"Зашифрованное сообщение SS для клиента: {{{response_K_C_SS}}}{K_C_SS}")

        print(f"SS отправляет сообщение клиенту: {response_K_C_SS}\n\n")
        return response_K_C_SS