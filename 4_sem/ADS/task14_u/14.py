def set_zero(a, diag):
    for i in range(n):
        for j in range(n):
            if (diag and i == j):
                a[i][j] = 1
                continue
            a[i][j] = 0

def copy(a, b):
    for i in range(n):
        for j in range(n):
            a[i][j] = b[i][j]

def mul(a, b):
    set_zero(buf_mul, False)

    for i in range(n):
        for j in range(n):
            for k in range(n):
                buf_mul[i][j] = int((buf_mul[i][j] + ((a[i][k] * b[k][j]) % m)) % m)

    copy(a, buf_mul)

def pow(a, p):
    set_zero(buf_pow, True)

    while p != 0:
        if p % 2 != 0:
            mul(buf_pow, a)
            p -= 1
        else:
            mul(a, a)
            p //= 2

    copy(a, buf_pow)

n, m = map(int, input().split())
u, v, l = map(int, input().split())

u -= 1
v -= 1

_mod = int(1e9 + 7)

r = []
buf_mul = []
buf_pow = []

for i in range(n):
    r.append([0]*n)
    buf_mul.append([0]*n)
    buf_pow.append([0]*n)

for _ in range(m):
    i, j = map(int, input().split())
    
    i -= 1
    j -= 1

    r[i][j] = 1
    r[j][i] = 1

    if (i == j):
        r[i][j] = 2
        r[j][i] = 2


pow(r, l)
print(int(r[u][v] % _mod))
