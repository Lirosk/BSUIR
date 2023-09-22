from operator import mod
import random
from hashlib import sha256


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

def find_prime(iNumBits, iConfidence):
		while(1):
				p = random.randint( 2**(iNumBits-2), 2**(iNumBits-1) )
				while( p % 2 == 0 ):
						p = random.randint(2**(iNumBits-2),2**(iNumBits-1))

				while( not SS(p, iConfidence) ):
						p = random.randint( 2**(iNumBits-2), 2**(iNumBits-1) )
						while( p % 2 == 0 ):
								p = random.randint(2**(iNumBits-2), 2**(iNumBits-1))

				q = p * 2 + 1
				if SS(p, iConfidence):
						return q, p


def hash_function(message):
    hashed = int(sha256(message.encode("UTF-8")).hexdigest(), 16)
    return hashed




def gcdExtended(a, b):
    if a == 0 :
        return b,0,1
    gcd,x1,y1 = gcdExtended(b%a, a)
    x = y1 - (b//a) * x1
    y = x1
    return gcd,x,y


p = 12491554796616397392007291845361681019980789084728846304013646795466302633346425772369277064638881858428879662416202925770315709968465491470753112581700067
q = 69008397991237478218529528711753578857464356221556536838757636132646301588781
g = 8305821956779628193852750508811757244889982632821843521491035713173371468528798753831744267407230704527461062321732669034432746173786958142572929772413468


#g = modexp(2, int((p-1)/q), p)
#print(g)


x = 21806766525219456845975433141440323207628356177928011376752764983262367199302

y = modexp(g, x, p)


k = 65563535523989486530471812563550844184252835357270278209669888582262919055146


r = modexp(g, k, p) % q



normal_text = 'Lorem ipsum'


s = (k * hash_function(normal_text) + x * r) % q


w = modexp(hash_function(normal_text), q-2, q)


u1 = (w * s) % q
u2 = ((q - r) * w) % q

v = ((modexp(g, u1, p) * modexp(y, u2, p))%p)% q 

print(v)
