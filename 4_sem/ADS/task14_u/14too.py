# Python3 implementation of the approach

import numpy as np

# Function to multiply two matrices
def multiply(a, b, res) :

	mul = np.zeros((N,N));
	
	for i in range(N) :
		for j in range(N) :
			mul[i][j] = 0;
			for k in range(N) :
				mul[i][j] += a[i][k] * b[k][j];

	# Storing the multiplication result in res[][]
	for i in range(N) :
		for j in range(N) :
			res[i][j] = mul[i][j];


# Function to compute G raised to the power n
def power(G, res, n) :
	
	# Base condition
	if (n == 1) :
		for i in range(N) :
			for j in range(N) :
				res[i][j] = G[i][j];
		return;

	# Recursion call for first half
	power(G, res, n // 2);

	# Multiply two halves
	multiply(G, G, res);

	# If n is odd
	if (n % 2 != 0) :
		multiply(res, G, res);

# Driver code
if __name__ == "__main__" :

	G = [
		[1]
		];
		
	N = len(G)

	k = int(1e9);
	res = np.zeros((N,N));

	power(G, res, k);

	for i in range(N) :
		for j in range(N) :
			print(res[i][j],end = " ");
		
		print()
		
# This code is contributed by AnkitRai01
