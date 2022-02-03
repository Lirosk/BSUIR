import numpy as np
from math import log10
import math

def main():
    a = 1
    b = 3
    int_acc = 1e-7
    diff_acc = 1e-2

    diffs = [diff, diff2]
    for dif in diffs:
        res = dif(f, (a + b) / 2, diff_acc)
        print(dif.__name__, ": ", round(res[0], int(abs(log10(diff_acc)))), "\niterations: ", res[1])

    print('\n')

    for i in integration:
        res = integrate(f, a, b, int_acc, i)
        print(i,": ", round(res[0], int(abs(log10(int_acc)))), "\niterations: ", res[1])

def f(x):
    return math.log10(x)

def left_rect(func, n, left, h):
    res = 0
    for i in range(int(n)):
        res += func(left + i * h)
    res *= h
    return res

def right_rect(func, n, left, h):
    res = 0
    for i in range(int(n)):
        res += func(left + (i + 1 / 2) * h)
    res *= h
    return res

def central_rect(func, n, left, h):
    res = 0
    for i in range(int(n)):
        res += func(left + (i + 1 / 2) * h)
    res *= h
    return res

def trapezium(func, n, left, h):
    res = 0
    for i in range(1, int(n)):
        res += func(left + i * h)
    res += 0.5 * (func(left + h * n) + func(left))
    res *= h
    return res

def simpson(func, n, left, h):
    right = left + n*h
    h=(right-left)/n
    k=0.0
    x = left + h
    for i in range(1,int(n/2 + 1)):
        k += 4*func(x)
        x += 2*h

    x = left + 2*h
    for i in range(1,int(n/2)):
        k += 2*func(x)
        x += 2*h
    return (h/3)*(func(left)+func(right)+k)

integration = {
    "left_rect": left_rect,
    "right_rect": right_rect,
    "central_rect": central_rect,
    "trapezium": trapezium,
    "simpson": simpson
}

def calculate_iterations(left, right, accuracy, power):
    h = np.power(accuracy, power)
    return (right - left) / h

def integrate(func, left, right, accuracy, _type, total=None):
		n = calculate_iterations(left, right, accuracy, 0.25)
		if (_type == "simpson"):
			n /= 2
		n = np.ceil(n)
		if (_type == "simpson"):
			n *= 2
        h = (right - left) / n
        I = integration[_type](func, n, left, h)
        I_prev = I + accuracy * 20
        counter = 0
        while abs(I - I_prev) > accuracy or (total is not None and counter < total):
            counter += 1
            I_prev = I
            h /= 2
            n *= 2
            I = integration[_type](func, n, left, h)
        return I, counter

def diff(func, x, accuracy):
    diff_ = 10 * accuracy
    h = 0.1
    derivative = 10 * accuracy
    derivative = (func(x + h) - func(x - h)) / (2 * h)
    counter = 0
    while abs(diff_) > accuracy:
        temp = derivative
        derivative = (func(x + h) - func(x - h)) / (2 * h)
        if counter != 0:
            diff_ = derivative - temp
        else:
            diff_ = 10 * accuracy
        h /= 4
        counter += 1
    return derivative, counter


def diff2(func, x, accuracy):
    diff_ = 10 * accuracy
    h = 0.1
    derivative = 10 * accuracy
    derivative = (func(x + h) - func(x - h)) / (2 * h)
    counter = 0
    h /= 4
    while abs(diff_) >= accuracy:
        temp = derivative
        derivative = (func(x + h) + func(x - h) - 2 * func(x)) / (h ** 2)
        diff_ = abs(derivative - temp)
        counter += 1
        h /= 2
    return derivative, counter

if __name__ == '__main__':
    main()


