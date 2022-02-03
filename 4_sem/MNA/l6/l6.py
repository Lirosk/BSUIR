import numpy as np
import matplotlib.pyplot as plt

def main() -> None:
    x = [0.0, 0.1,  0.2,  0.3,  0.4,  0.5,  0.6,  0.7, 0.8,  0.9,  1.0]
    p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]

    

    k = 1
    m = 0

    d = {}
    for i in range(len(x)):
        d[x[i]] = p[i]


    def yf(x):
        res = d[x] + m * (-1)**k
        return res

    y = []
    for i in x:
        y.append(yf(i))


    x = np.array(x)
    y = np.array(y)

    xa = np.linspace(x[0], x[-1], 100)
    ya = [lagrangeLAGRANGElagrange(x, y, i) for i in xa]
    print(v1 := ya[47])

    print(pn)

    m = abs(pn[0])
    for i in range(1, len(pn)):
        if abs(pn[i]) > m:
            m = abs(pn[i])
    print(m)

    fig = plt.figure()

    ax1 = fig.add_subplot(211)
    ax1.plot(x, y, 'o', xa, ya)
    ax1.grid(True)
    ax1.set_title('LAGRANGE')

    ya = newtoneNEWTONEnewtone(x, y)
    print(v2 := ya[47])

    ax2 = fig.add_subplot(212)
    ax2.plot(x, y, 'o', xa, ya)
    ax2.grid(True)
    ax2.set_title('NEWTONE')

    fig.tight_layout()
    plt.show()

    print("Error at point 0.47 is: ", abs(v1 - v2))


def newtoneNEWTONEnewtone(x: list, y: list) -> list:
    def omega(x, val, n):
        mul = 1
        for i in range(n):
            if i: 
                mul *= val - x[i-1]
            yield mul
    C=[]

    for n in range(len(x)):
        p = omega(x, x[n], n+1)
        C.append((y[n] - sum(C[k] * next(p) for k in range(n))) / next(p))

    def f(v):
        return sum(C[k]*p for k, p in enumerate(omega(x, v, len(C))))

    xa = np.linspace(x[0], x[-1], 100)

    ya = []
    for i in xa:
        ya.append(f(i))

    return ya

def lagrangeLAGRANGElagrange(x: float, y: float, t: float) -> float:
    z = 0
    for j in range(len(y)):
        p1 = 1
        p2 = 1
        for i in range(len(x)): 
            if i != j:
                p1 *= (t - x[i])
                p2 *= (x[j] - x[i])
        z += y[j] * p1 / p2
    return z

if __name__ == '__main__':
    main()