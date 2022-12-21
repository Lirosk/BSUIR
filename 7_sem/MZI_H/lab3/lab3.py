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

file_to_enc = open(os.path.join(dir_path, 'source.txt'), 'r')
m = file_to_enc.read()
file_to_enc.close()


c = rsa_encrypt(m, publicKey)
file_encrypted = open(os.path.join(dir_path, 'encrypted.txt'), 'w')
file_encrypted.write(''.join(map(lambda x: f'{hex(x)[2:]:02}', c)))
file_encrypted.close()

d = rsa_decrypt(c, privateKey)
decrypted_file = open(os.path.join(dir_path, 'decrypted.txt'), 'w')
decrypted_file.write(d)
decrypted_file.close()
