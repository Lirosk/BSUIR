import unittest
import os

from Crypto.Util.Padding import pad, unpad
from Crypto.Cipher import DES, DES3
from Crypto import Random


dir_path = os.path.dirname(os.path.realpath(__file__))


def des_encrypt(key, msg, pad_block_size=8):
    cipher = DES.new(key, DES.MODE_ECB)
    msg = cipher.encrypt(pad(msg.encode('utf-8'), pad_block_size))
    return msg


def des_decrypt(key, msg, pad_block_size=8):
    decipher = DES.new(key, DES.MODE_ECB)
    msg = decipher.decrypt(msg)
    msg = unpad(msg, pad_block_size).decode('utf-8')
    return msg


def prepare_des_key(key, pad_block_size=8):
    return pad(key.encode('utf-8'), pad_block_size)


def des3_encrypt(key, iv, msg, pad_block_size=8):
    encipher = DES3.new(key, DES3.MODE_OFB, iv)
    msg = encipher.encrypt(pad(msg.encode('utf-8'), pad_block_size))
    return msg


def des3_decrypt(key, iv, msg, pad_block_size=8):
    decipher = DES3.new(key, DES3.MODE_OFB, iv)
    msg = decipher.decrypt(msg)
    msg = unpad(msg, pad_block_size).decode('utf-8')
    return msg


def prepare_des3_key(key, pad_key_size=16):
    return pad(key.encode('utf-8'), pad_key_size)


def prepare_iv(pad_block_size=8):
    return Random.new().read(pad_block_size)  # DES3.block_size==8


class TestStringMethods(unittest.TestCase):
    def test_des(self):
        key = 'key'
        block_size = 8
        key = prepare_des_key(key, block_size)
        # 1. Open file 'des3_to_enc.txt' & read text
        with open(os.path.join(dir_path, 'des_to_enc.txt'), 'r') as file_to_enc:
            normal_text = file_to_enc.read()
            # 2. Encrypt read text
            encrypted_text = des_encrypt(key, normal_text, block_size)
            print()
            print(''.join(map(lambda x: str(x), encrypted_text)))
            print()
            # 3. Encrypt decrypted text
            decrypted_text = des_decrypt(key, encrypted_text, block_size)
            # 4. Save decrypted text to 'decrypted.txt'
            with open(os.path.join(dir_path, 'des_dec.txt'), 'w') as decrypted_file:
                decrypted_file.write(decrypted_text)
                self.assertEqual(normal_text, decrypted_text)

    def test_des3(self):
        key = 'key'
        key_size = 16
        block_size = 8
        key = prepare_des3_key(key, key_size)
        iv = prepare_iv(block_size)
        # 1. Open file 'des3_to_enc.txt' & read text
        with open(os.path.join(dir_path, 'des_to_enc.txt'), 'r') as file_to_enc:
            normal_text = file_to_enc.read()
            # 2. Encrypt read text
            encrypted_text = des3_encrypt(key, iv, normal_text)
            print()
            print(encrypted_text.hex())
            print()
            # 3. Encrypt decrypted text
            decrypted_text = des3_decrypt(key, iv, encrypted_text)
            # 4. Save decrypted text to 'decrypted.txt'
            with open(os.path.join(dir_path, 'des_dec.txt'), 'w') as decrypted_file:
                decrypted_file.write(decrypted_text)
                self.assertEqual(normal_text, decrypted_text)


if __name__ == '__main__':
    unittest.main()
