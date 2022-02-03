import matplotlib.pyplot as plt
from math import exp
from numpy import linspace
import math

def main():
    x = [-3, -2, -1, 0, 1, 2, 3]
    y = [f(i) for i in x]
    plt.scatter(x, y, label = "nodes")

    spline = BuildSpline(x, y, len(x))[1:]

    for i in range(len(spline)):
        s = spline[i]
        
        print("xi = ", s.x)
        print("coefs from ai to di:\n", [s.a, s.b, s.c, s.d], f" x from {x[i]} to {x[i+1]}\n")#, f"for x from {x[i]} to {x[i+1]}\n")

    x0 = 2
    print("Value of spline in x = 0.5*(b-a) =", Interpolate(spline, x0))
    print("Value of func minus value of spline", exp(-x0) - Interpolate(spline, x0))

    x = linspace(-3, 3, 100)
    y = [f(i) for i in x]
    yi = [Interpolate(spline, i) for i in x]

    plt.plot(x, y, label = "f(x)")
    plt.plot(x, yi, label = "spline")
    plt.legend()
    plt.show()


def f(x):
    return exp(-x)


def sign(a):
    if a < 0:
        return -1
    if a > 0:
        return 1
    return 0


class Spline:
    def __init__(self, a, b, c, d, x):
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.x = x
 

def BuildSpline(x, y, n):
    splines = [Spline(0, 0, 0, 0, 0) for _ in range(0, n)]
    for i in range(0, n):
        splines[i].x = x[i]
        splines[i].a = y[i]
    
    splines[0].c = splines[n - 1].c = 0.0
    
    alpha = [0.0 for _ in range(0, n - 1)]
    beta  = [0.0 for _ in range(0, n - 1)]
 
    for i in range(1, n - 1):
        hi  = x[i] - x[i - 1]
        hi1 = x[i + 1] - x[i]
        A = hi
        C = 2.0 * (hi + hi1)
        B = hi1
        F = 6.0 * ((y[i + 1] - y[i]) / hi1 - (y[i] - y[i - 1]) / hi)
        z = (A * alpha[i - 1] + C)
        alpha[i] = -B / z
        beta[i] = (F - A * beta[i - 1]) / z
  
    for i in range(n - 2, 0, -1):
        splines[i].c = alpha[i] * splines[i + 1].c + beta[i]
    
    for i in range(n - 1, 0, -1):
        hi = x[i] - x[i - 1]
        splines[i].d = (splines[i].c - splines[i - 1].c) / hi
        splines[i].b = hi * (2.0 * splines[i].c + splines[i - 1].c) / 6.0 + (y[i] - y[i - 1]) / hi
    return splines
 
def Interpolate(splines, x):
    if not splines:
        return None
    
    n = len(splines)
    s = Spline(0, 0, 0, 0, 0)
    
    if x <= splines[0].x:
        s = splines[0]
    elif x >= splines[n - 1].x:
        s = splines[n - 1]
    else:
        i = 0
        j = n - 1
        while i + 1 < j:
            k = i + (j - i) // 2
            if x <= splines[k].x:
                j = k
            else:
                i = k
        s = splines[j]
    
    dx = x - s.x
    return s.a + (s.b + (s.c / 2.0 + s.d * dx / 6.0) * dx) * dx
    
 
if __name__ == '__main__':
    main()
