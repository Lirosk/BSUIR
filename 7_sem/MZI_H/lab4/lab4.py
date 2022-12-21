import random
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

def gcd( a, b ):
		while b != 0:
			c = a % b
			a = b
			b = c
		return a


def modexp( base, exp, modulus ):
		return pow(base, exp, modulus)

def SS( num, iConfidence ):
		for i in range(iConfidence):
				a = random.randint( 1, num-1 )
				if gcd( a, num ) > 1:
						return False

				if not jacobi( a, num ) % num == modexp ( a, (num-1)//2, num ):
						return False
		return True


def jacobi( a, n ):
		if a == 0:
				if n == 1:
						return 1
				else:
						return 0
		elif a == -1:
				if n % 2 == 0:
						return 1
				else:
						return -1
		elif a == 1:
				return 1
		elif a == 2:
				if n % 8 == 1 or n % 8 == 7:
						return 1
				elif n % 8 == 3 or n % 8 == 5:
						return -1

		elif a >= n:
				return jacobi( a%n, n)
		elif a%2 == 0:
				return jacobi(2, n)*jacobi(a//2, n)

		else:
				if a % 4 == 3 and n%4 == 3:
						return -1 * jacobi( n, a)
				else:
						return jacobi(n, a )


def find_primitive_root( p ):
		if p == 2:
				return 1
		p1 = 2
		p2 = (p-1) // p1

		while( 1 ):
				g = random.randint( 2, p-1 )
				if not (modexp( g, (p-1)//p1, p ) == 1):
						if not modexp( g, (p-1)//p2, p ) == 1:
								return g


def find_prime(iNumBits, iConfidence):
		while(1):
				p = random.randint( 2**(iNumBits-2), 2**(iNumBits-1) )
				while( p % 2 == 0 ):
						p = random.randint(2**(iNumBits-2),2**(iNumBits-1))

				while( not SS(p, iConfidence) ):
						p = random.randint( 2**(iNumBits-2), 2**(iNumBits-1) )
						while( p % 2 == 0 ):
								p = random.randint(2**(iNumBits-2), 2**(iNumBits-1))

				p = p * 2 + 1
				if SS(p, iConfidence):
						return p


def encrypt(message, g, y, p):
    en_msg = []

    k = random.randint(2, p-2)  


    a = modexp(g, k, p)


    b = modexp(y, k, p)

    for i in range(0, len(message)):
        en_msg.append(message[i])

    for i in range(0, len(en_msg)):
        en_msg[i] = (b * ord(en_msg[i])) % p

    return a, en_msg


def decrypt(en_message, x, p, a):
    dr_message = []
    for i in range(0, len(en_message)):
        en_message[i] = (en_message[i] * modexp(a, p-1-x, p)) % p
    for i in range(0, len(en_message)):
        dr_message.append(chr(int(en_message[i])))

    return dr_message


p = find_prime(256, 32)

g = find_primitive_root( p )

x = random.randint(2, p-2)

y = modexp(g, x, p)


file_to_enc = open(os.path.join(dir_path, 'source.txt'), 'r')
normal_text = file_to_enc.read()
file_to_enc.close()

a, encrypted_text = encrypt(normal_text, g, y, p)

encrypted_file = open(os.path.join(dir_path, 'encrypted.txt'), 'w')
encrypted_file.write(''.join(map(lambda x: str(x), encrypted_text)))
encrypted_file.close()

decrypted_text = decrypt(encrypted_text, x, p, a)
decrypted_text = ''.join(decrypted_text)

decrypted_file = open(os.path.join(dir_path, 'decrypted.txt'), 'w')
decrypted_file.write(decrypted_text)
decrypted_file.close()
