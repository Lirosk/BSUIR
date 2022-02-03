import numpy as np
import matplotlib.pyplot as plt

k = 2

a = np.sin(k)
b = np.cos(k)

A = -1
B = 1

def q(x):
    return (1 + b * x * x) / a

def f(x):
    return -1 / a

def p(x):
    return 0

def решить_разностной_схемой(p, q, f, A, B, Ua, Ub, n=2_000, *, check=True):
    if check and n > 2_000:
        n = 2_000

    h = (B - A) / n
    xs = [(round(x, 3) if check else x) for x in np.linspace(A, B, n + 1)]

    diags = [
        [(1 + h * p(x) / 2) for x in xs],
        [(1*h*h*q(x) - 2) for x in xs],
        [(1 - h * p(x) / 2) for x in xs]
    ]

    syst = []
    for _ in range(n+1):
        syst.append([0]*(n+1))

    syst[0][0] = 1
    syst[-1][-1] = 1

    i = 1
    j = 1
    while i < n:
        syst[i][j+1] = diags[2][i+1]    # k+1
        syst[i][j] = diags[1][i]      # k
        syst[i][j-1] = diags[0][i-1]    # k-1
        i += 1
        j += 1    

    vec = [h * h * f(x) for x in xs]
    vec[0] = Ua
    vec[-1] = Ub

    ys = np.linalg.solve(syst, vec)

    return xs, ys

xs, ys = решить_разностной_схемой(p, q, f, A, B, Ua=0, Ub=0)
n = len(xs)

grid_func = list(zip(xs, [round(y, 3) for y in ys]))

print('(x: y(x))')
print(f'''
{grid_func[:11]}...

...{grid_func[(n+1)//2 - 5: (n+1)//2 + 5 + 1]}...

...{grid_func[-11:]}
''' if len(grid_func) > 10 else grid_func)

plt.plot(xs, ys)
plt.title("разностной схемой")
plt.grid()
plt.show()


# u(a) = Ua
# u(b) = ub

A = 0
B = 2
Ua = 0
Ub = 5
eps = 0.05

def p(x):
    return np.exp(-x*x)

def q(x):
    return 5 * (2 + np.sin(2 * x))

def f(x):
    return np.exp(x) * (1 + np.sin(2 * x))


n = 4

xs_pre, ys_pre = решить_разностной_схемой(p, q, f, A, B, Ua, Ub, n=n, check=False)

found = False
while not found:
    n *= 2
    xs_post, ys_post = решить_разностной_схемой(p, q, f, A, B, Ua, Ub, n=n, check=False)

    tmp = ys_post[::2]

    for i in range(1, len(ys_pre) - 1):
        if abs(ys_pre[i] - tmp[i]) > eps:
            found = False
            break
        found = True

    plt.plot(xs_pre, ys_pre, label=f"n = {n//2}")
    plt.plot(xs_post, ys_post, label=f"{n = }")
    plt.title("разностной схемой")
    plt.legend()
    plt.grid()
    plt.show()
    
    xs_pre = xs_post[:]
    ys_pre = ys_post[:]

    if n > 2000:
        break

A = 0.4
B = 1.4
Ua = 1.2
Ub = ...

eps = 0.05

def p(x):
    return -0.5 * x

def q(x):
    return 1

def f(x):
    return 2

def решить_разностной_схемой3(p, q, f, A, B, Ua, Ub, n=2_000, *, check=True):
    if check and n > 2_000:
        n = 2_000

    h = (B - A) / n
    xs = [(round(x, 3) if check else x) for x in np.linspace(A, B, n + 1)]

    diags = [
        [(1 - h * p(x) / 2) for x in xs],
        [(1*h*h*q(x) - 2) for x in xs],
        [(1 + h * p(x) / 2) for x in xs],
    ]

    syst = []
    for _ in range(n+1):
        syst.append([0]*(n+1))

    syst[0][0] = 1
    syst[-1][-1] = 1

    i = 1
    j = 1
    while i < n:
        syst[i][j+1] = diags[2][i+1]    # k+1
        syst[i][j] = diags[1][i]      # k
        syst[i][j-1] = diags[0][i-1]    # k-1
        i += 1
        j += 1    
    syst[-1][-1] = 1+h
    syst[-1][-2] = -1

    vec = [h * h * f(x) for x in xs]
    vec[0] = Ua
    vec[-1] = 3.2 * h

    ys = np.linalg.solve(syst, vec)

    return xs, ys

xs, ys = решить_разностной_схемой3(p, q, f, A, B, Ua, Ub)

plt.plot(xs, ys)
plt.title("разностной схемой")
plt.grid()
plt.show()