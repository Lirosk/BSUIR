import numpy

n, m = input().split()
n = int(n)
m = int(m)

u, v, l = input().split()
u = int(u) - 1
v = int(v) - 1
l = int(l)

r = numpy.array([numpy.array([0 for _ in range(n)]) for __ in range(n)])

for i in range(m):
    i, j = input().split()
    i = int(i) - 1
    j = int(j) - 1

    r[i][j] = 1
    r[j][i] = 1

r=r**l
print(r[u][v])