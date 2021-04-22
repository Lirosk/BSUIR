import numpy as np
import funcs
from data import C, D, b

if (input("Use standart data?('y' if yes): ").strip().lower() == "y"):
	k = int(input("Enter ur variant: "))

	A = k * np.array(C) + np.array(D)
	del C, D
else:
	size = int(input("Enter size of array: ")) 
	B = []
	for i in range(size):
		B.append([float(y) for y in input().split()])
	A = [x[:-1] for x in B]
	b = [x[-1] for x in B]

	del B

A = np.array(A)

print("\n")
methods = (funcs.sImPlEiTeRaTiOnSmeThoD, funcs.gAuSsSeIdeLmEtHoD)
for m in methods:
	res = m(A, b)
	print(f"{res}")
print("\n")

'''
20 2 3 7 5
1 12 -2 -5 4
5 -3 13 0 -3
0 0 -1 15 7

answers: (0.0614, 0.495, -0.14, 0.457)
'''

'''
4 1 1 9
1 6 -1 10
1 2 5 20

ansers: (1, 2, 3)
'''

'''
32 2 1 3 1 43
1 8 3 1 3 14
1 2 16 3 1 -3
1 2 3 56 1 169
1 2 1 3 32 -19

answers: (1, 2, -1, 3, -1)
'''

'''
1.34  0.21  0.15  0.12 -0.13 1.2
-0.12 -1.32  0.09  0.17  0.12 2.2
0.12 -0.12 -1.32  0.11  0.15 4
0.17  0.12 -0.12 -1.32 -0.11 0
0.11  0.67  0.12 -0.12 -1.32 -1.2

answers: (1.466, -1.975, -2.769, 0.282, -0.249)
'''