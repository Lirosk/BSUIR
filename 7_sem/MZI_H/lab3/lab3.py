import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

def extendGcd(a, b): # Расширенный алгоритм Евклида для решения уравнения Безу
    if b == 0:
        x = 1
        y = 0
        return x, y
    else:
        x1, y1 = extendGcd(b, a % b)
        x = y1
        y = x1 - (int)(a / b) * y1
        return x, y
    
def generateKey(p, q):
    n = p * q  
    fn = (p - 1) * (q - 1)     
    e = 7 # ввести вручную
    x, y = extendGcd(e, fn) 
    if x < 0: 
        x = x + fn
    d = x
    return (n, e),(n, d) 

def rsa_encrypt(plaintext, publicKey):
    n = publicKey[0]
    key = publicKey[1]
    cipher = [(ord(char) ** key) % n for char in plaintext]
    return cipher


def rsa_decrypt(ciphertext, privateKey):
    n = privateKey[0]
    key = privateKey[1]
    plain = [chr((char ** key) % n) for char in ciphertext]
    return ''.join(plain) 


p = 13
q = 17
publicKey, privateKey = generateKey(p, q)
file_to_enc = open(os.path.join(dir_path, 'rsa_to_enc.txt'), 'r')
m = file_to_enc.read()
print('Открытый текст: % s' % m)
c = rsa_encrypt(m, publicKey)
print('Зашифрованный текст: % s' % c)
d = rsa_decrypt(c, privateKey)
print('Обычный текст после расшифровки: % s' % d)
decrypted_file = open(os.path.join(dir_path, 'rsa_decrypted.txt'), 'w')
decrypted_file.write(d)
