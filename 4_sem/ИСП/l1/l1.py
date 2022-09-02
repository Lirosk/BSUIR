import numpy as np


############################

def swap(a, b):
	if (type(a) == list and type(b) == list):
		temp = a.copy()
		a = b.copy()
		b = temp.copy()
		del temp
		return

	a, b = b, a

############################

def ZeroColumn(arr, row):
	l = len(arr)

	for scndRow in range(row + 1, l):
		if (arr[row, row] == 0):
			swapped = False

			for temp in range(l - 1, row, -1):
				if (arr[temp,row] != 0):
					swap(arr[temp], arr[row])
					swapped = True
					break

			if (not swapped):
				break

		arr[scndRow] -= arr[row] * arr[scndRow, row] / arr[row, row]

############################

def Backward(arr):
	l = len(arr)
	ll = len(arr[0])

	for row in range(l - 1, 0, -1):
		for scndRow in range(row):
			if (arr[row, ll - 2 - (l - 1 - row)] == 0):
				continue
			arr[scndRow] -= arr[row] * arr[scndRow, ll - 2 - (l - 1 - row)] / arr[row, ll - 2 - (l - 1 - row)]

	for row in range(l):
		arr[row] /= arr[row, row]
		arr[row] = [round(x, fr) for x in arr[row]]

############################

def Gauss(arr):
	l = len(arr)	

	for row in range(l - 1):
		ZeroColumn(arr, row)

	Backward(arr)

############################

def GaussByGreaterElementInColumn(arr):
	l = len(arr)
	ll = len(arr[0])

	for row in range(l - 1):
		
		max = abs(arr[row, row])
		k = row
		for j in range(row + 1, l):
			if (abs(arr[j, row]) > max):
				max = (arr[j, row])
				k = j

		if (k != row):
			swap(arr[k], arr[row])

		ZeroColumn(arr, row)

	Backward(arr)

############################

def GaussByGreaterElementInArray(arr):
	l = len(arr)
	ll = len(arr[0])

	for row in range(l - 1):
		
		max = abs(arr[row, row])
		k = row
		
		for i in range(row, l):
			for j in range(row, l):
				if (abs(arr[i, j]) > max):
					max = abs(arr[i,j])
					k = i

		if (k != row):
			swap(arr[k], arr[row])

		ZeroColumn(arr, row)

	Backward(arr)

############################


b =  np.array([
	[4.2],
	[4.2],
	[4.2],
	[4.2],
	[4.2]
	])


C = np.array([
	[0.2, 0, 0.2, 0, 0],
	[0, 0.2, 0, 0.2, 0],
	[0.2, 0, 0.2, 0, 0.2],
	[0, 0.2, 0, 0.2, 0],
	[0, 0, 0.2, 0, 0.2]
	])

D = np.array([
	[2.33 , 0.81, 0.67 , 0.92, -0.53],
	[-0.53, 2.33, 0.81, 0.67, 0.92],
	[0.92, -0.53, 2.33, 0.81, 0.67],
	[0.67, 0.92, -0.53, 2.33, 0.81],
	[0.81, 0.67, 0.92, -0.53, 2.33]
	])

fr = 4


if (input("Use standart data?('y' if yes): ").strip().lower() == "y"):
	k = int(input("Enter ur variant: "))

	A = k * C + D
	copy = A.copy()
	del C, D

	B = A.copy()
	A = A.tolist()
	for row in range(len(A)):
		A[row].append(float(b[row]))
else:
	size = int(input("Enter size of array: ")) 
	A = []
	for x in range(size):
		A.append([float(y) for y in input().split()])

	B = [x[:-1] for x in A]

B = np.array(B)
A = np.array(A)

#критерий единственности решения
if not (np.linalg.matrix_rank(A) == np.linalg.matrix_rank(B) == len(B[0])):
	print("\nUniqueness criterion for solution is not satisfied!\n")
	exit()

copy = A.copy()
methods = [Gauss, GaussByGreaterElementInColumn, GaussByGreaterElementInArray]

print("\nAnswer by all methods:\n")
for m in methods:
	A = copy.copy()
	m(A)
	ans = [A[i, len(A)] for i in range(len(A))]
	print(ans, "\n")



'''
3 2 -5 -1
2 -1 3 13
1 2 -1 9

answer: (3, 5, 4)
'''


'''
1 2 3 1
2 -1 2 6
1 1 5 -1

answer: (4, 0, -1)
'''


'''
2 5 4 1 20
1 3 2 1 11
2 10 9 7 40
3 8 9 2 37

answer: (1, 2, 2, 0)
'''


n: int = int(input("Enter number: "))
primes = 
	[2] + 
	[x for x in range(3, n + 1, 2) 
		if list(filter(lambda i: x/i == x//i, range(3, x + 1, 2)))[0] == x]

print(primes)

def fib(n: int) -> int:
	if (n < 3):
		return 1
	if (n < 0):
		return 0
	return f(n - 1) + f(n - 2)


