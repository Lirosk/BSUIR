import numpy as np
from scipy import integrate
import matplotlib.pyplot as plt

k = 2
a = np.sin(k)
b = np.cos(k)

A = -1
B = 1

def phi(i, x):
    if i < 1:
        return 0
    return np.power(x, i-1)*(1-x*x)

def ddphi(i, x):
    if i < 1:
        return 0
    elif i == 1:
        return -2
    elif i == 2:
        return -6*x
    return (i-1)*(i-2)*x**(i-3)-i*(i+1)*x**(i-1)

def q(x):
    return (1+b*x*x)

def f(x):
    return -1
    
def y(x):
    res = phi(0, x)
    for i in range(len(ais)):
        res += ais[i] * phi(i + 1, x)
    return res

# y(n, x) = phi(0, x) + a1*phi(1, x) + ... + an*phi(n, x)
# ddy(n, x) = ddphi(0, x) + a1*ddphi(1, x) + ... + an*ddphi(n, x)
# psi(x, a1, ..., an) = a*ddy(n, x) + q(x)*y(n, x) - f(x)

def k(i, x):
    return a * ddphi(i, x) + q(x) * phi(i, x)

def c(x):
    return f(x) - a * ddphi(0, x) - q(x) * phi(0, x) 

n = 100
xs = np.linspace(A, B, n)

syst = []
vec = []

for x in xs:
    r = []
    for i in range(n):
        r.append(k(i+1, x))
    syst.append(r)
    vec.append(c(x))

ais = np.linalg.solve(syst, vec) 
ys = [y(x) for x in xs]

grid_func = list(zip(xs, ys))
print(grid_func[:10], "...")
print("...", grid_func[-10:])

plt.plot(xs, ys, label=f"n = {n}, [a, b] = [{A}, {B}]")
plt.title("Коллокаций")
plt.legend()
plt.grid()
plt.show()

def k(i, j):
    res = a * integrate.quad(lambda x: phi(i, x) * ddphi(j, x), A, B)[0] + \
            integrate.quad(lambda x: q(x) * phi(i, x) * phi(j, x), A, B)[0]
    return res

def c(i):
    res = -(integrate.quad(lambda x: phi(i, x) * ddphi(0, x), A, B)[0] + \
            integrate.quad(lambda x: q(x) * phi(i, x) * phi(0, x), A, B)[0] + \
            integrate.quad(lambda x: phi(i, x), A, B)[0])
    return res

syst = []
vec = []

for i in range(1, n + 1):
    r = []
    for j in range(1, n + 1):
        r.append(k(i, j))
    syst.append(r)
    vec.append(c(i))

ais = np.linalg.solve(syst, vec)

ys = [y(x) for x in xs]

grid_func = list(zip(xs, ys))
print(grid_func[:10], "...")
print("...", grid_func[-10:])

plt.plot(xs, ys, label=f"n = {n}, [a, b] = [{A}, {B}]")
plt.title("Галеркина")
plt.legend()
plt.grid()
plt.show()

N = 2*n

xs = np.linspace(A, B, N)

def k(i, j):
    res = 0
    for x in xs:
        res += (a * ddphi(i, x) + q(x)*phi(i, x)) * \
                (a * ddphi(j, x) + q(x) * phi(j, x))
    res *= 2 
    return res

def c(i):
    res = 0
    for x in xs:
        res += (a * ddphi(i, x) + q(x)*phi(i, x)) * \
                (a * ddphi(0, x) + q(x) * phi(0, x) + 1)
    res *= -2 
    return res

syst = []
vec = []

for i in range(1, n + 1):
    r = []
    for j in range(1, n + 1):
        r.append(k(i, j))
    syst.append(r)
    vec.append(c(i))

ais = np.linalg.solve(syst, vec)

ys = [y(x) for x in xs]

grid_func = list(zip(xs, ys))
print(grid_func[:10], "...")
print("...", grid_func[-10:])

plt.plot(xs, ys, label=f"n = {n}, N = {N}, [a, b] = [{A}, {B}]")
plt.title("Наименьших квадратов (дискретный)")
plt.legend()
plt.grid()
plt.show()

n = 100
xs = np.linspace(A, B, n)

def k(i, j):
    res = integrate.quad(
        lambda x: \
            (ddphi(j, x) + q(x) * phi(j, x)) * \
            (ddphi(i, x) + q(x) * phi(i, x)),
        A, B)[0]
    return res

def c(i):
    res = integrate.quad(
        lambda x: f(x) * ( ddphi(i, x) + q(x)*phi(i, x)),
        A, B)[0]
    return res

syst = []
vec = []

for i in range(1, n+1):
    r = []
    for j in range(1, n+1):
        r.append(k(i, j))
    syst.append(r)
    vec.append(c(i))

ais = np.linalg.solve(syst, vec)

ys = [y(x) for x in xs]

grid_func = list(zip(xs, ys))
print(grid_func[:10], "...")
print("...", grid_func[-10:])

plt.plot(xs, ys, label=f"n = {n}, [a, b] = [{A}, {B}]")
plt.title("Наименьших квадратов (интегральный)")
plt.legend()
plt.grid()
plt.show()