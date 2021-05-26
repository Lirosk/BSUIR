import numpy as np
import matplotlib.pyplot as plt

def differentiate(func, h, oldY, oldX):
    size = len(oldY)
    dY = np.array([oldY[i] - (oldY[i] + h * func(oldX[i], oldY[i])) for i in range(1, size)])
    dY = abs(dY)
    return dY.max()

def add_points(func, init_v_, h):
    points = [[init_v_[0]], [init_v_[1]]]
    points[0].append(points[0][0] + h)
    temp = []
    temp.append(h * func(points[0][0], points[1][0]))
    temp.append(h * func(points[0][0] + h / 2, points[1][0] + temp[0] / 2))
    temp.append(h * func(points[0][0] + h / 2, points[1][0] + temp[1] / 2))
    temp.append(h * func(points[0][0] + h, points[1][0] + temp[2]))
    points[1].append(points[1][0] + (1 / 6) * (temp[0] + temp[3] + 2 * (temp[1] + temp[2])))
    return points

def adams_method(func, _range, init_v_, accuracy):
    n = 2
    h = (_range[1] - _range[0]) / n
    points = add_points(func, init_v_, h)
    for i in range(int(n) - 1):
        points[0].append(points[0][i + 1] + h)
        points[1].append(points[1][i + 1] + h * ((3 / 2) * func(points[0][i + 1], points[1][i + 1]) - (1 / 2) * func(points[0][i], points[1][i])))
    diff = accuracy * 4
    while diff > accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = add_points(func, init_v_, h)
        for i in range(int(n) - 1):
            points[0].append(points[0][i + 1] + h)
            points[1].append(points[1][i + 1] + h * ((3 / 2) * func(points[0][i + 1], points[1][i + 1]) - (1 / 2) * func(points[0][i], points[1][i])))
        diff = differentiate(func, h, points_temp[1], points_temp[0])
    plt.plot(points[0], points[1], color='navy',label="adams")
    return None

def f(x, y):
    res = (a * (1 - y ** 2)) / ((1 + m) * x ** 2 + y ** 2 + 1)
    return res

m = 1.
a = .5
init_v = (0, 0)
_range = [0, 1]
acc = 1e-3

def main():
    adams_method(f, _range, init_v, acc)
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()
