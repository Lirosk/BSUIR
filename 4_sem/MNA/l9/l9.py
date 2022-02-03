import numpy as np
import matplotlib.pyplot as plt

def f(x, y):
    res = (a * (1 - y ** 2)) / ((1 + m) * x ** 2 + y ** 2 + 1)
    return res

solution_range = [0, 1]
initial_value = (0, 0)

a = 0.5
m = 1.
acc = 1e-3
fr = int(abs(np.log10(acc)))

def main():
    tasks = [euler_method, runge_method, modified_euler]
    for task in tasks:
        res = task(f, solution_range, initial_value, acc)
        print("step: ", res[2])
        print("values (x, y):\n", res[1])
        print("\n")
    plt.legend()
    plt.show()

def euler_method(func, _range, init_v, accuracy):
    n = 2
    h = (_range[1] - _range[0]) / n
    points = [[init_v[0]], [init_v[1]]]
    for i in range(int(n)):
        points[0].append(points[0][i] + h)
        points[1].append(points[1][i] + h * func(points[0][i], points[1][i]))
    diff = accuracy * 4
    while diff > accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = [[init_v[0]], [init_v[1]]]
        for i in range(int(n)):
            points[0].append(points[0][i] + h)
            points[1].append(points[1][i] + h * func(points[0][i], points[1][i]))
        diff = differentiate(func, h, points_temp[1], points_temp[0])
    plt.plot(points[0], points[1], color='blue', label="eueler method", linewidth=1)

    _points = [(round(points[0][i], fr), round(points[1][i], fr)) for i in range(len(points[0]))]
    return n, _points, round(h, fr)

def runge_method(func, _range, init_v, accuracy):
    n = 2
    h = (_range[1] - _range[0]) / n
    points = [[init_v[0]], [init_v[1]]]
    for i in range(int(n)):
        points[0].append(points[0][i] + h)
        tmp = []
        tmp.append(h * func(points[0][i], points[1][i]))
        tmp.append(h * func(points[0][i] + h / 2, points[1][i] + tmp[0] / 2))
        tmp.append(h * func(points[0][i] + h / 2, points[1][i] + tmp[1] / 2))
        tmp.append(h * func(points[0][i] + h, points[1][i] + tmp[2]))
        points[1].append(points[1][i] + (1 / 6) * (tmp[0] + tmp[3] + 2 * (tmp[1] + tmp[2])))
    diff = accuracy * 4
    while diff > accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = [[init_v[0]], [init_v[1]]]
        for i in range(int(n)):
            points[0].append(points[0][i] + h)
            tmp = []
            tmp.append(h * func(points[0][i], points[1][i]))
            tmp.append(h * func(points[0][i] + h / 2, points[1][i] + tmp[0] / 2))
            tmp.append(h * func(points[0][i] + h / 2, points[1][i] + tmp[1] / 2))
            tmp.append(h * func(points[0][i] + h, points[1][i] + tmp[2]))
            points[1].append(points[1][i] + (1 / 6) * (tmp[0] + tmp[3] + 2 * (tmp[1] + tmp[2])))
        diff = differentiate(func, h, points_temp[1], points_temp[0])
    plt.plot(points[0], points[1], color='red', label="runge method", linewidth=1)

    _points = [(round(points[0][i], fr), round(points[1][i], fr)) for i in range(len(points[0]))]
    return n, _points, round(h, fr)

def modified_euler(func, _range, init_v, accuracy):
    n = 2
    h = (_range[1] - _range[0]) / n
    points = [[init_v[0]], [init_v[1]]]
    for i in range(int(n)):
        points[0].append(points[0][i] + h)
        points[1].append(points[1][i] + h * func(points[0][i] + h / 2, points[1][i] + (h / 2) * func(points[0][i], points[1][i])))
    diff = accuracy * 4
    while diff > accuracy:
        points_temp = points.copy()
        n *= 2
        h /= 2
        points = [[init_v[0]], [init_v[1]]]
        for i in range(int(n)):
            points[0].append(points[0][i] + h)
            points[1].append(points[1][i] + h * func(points[0][i] + h / 2, points[1][i] + (h / 2) * func(points[0][i], points[1][i])))
        diff = differentiate(func, h, points_temp[1], points_temp[0])
    plt.plot(points[0], points[1], color='green', label="mod euler", linewidth=1)

    _points = [(round(points[0][i], fr), round(points[1][i], fr)) for i in range(len(points[0]))]
    return n, _points, round(h, fr)

def differentiate(f, h, last_y, last_x):
    size = len(last_y)
    dY = np.array([last_y[i] - (last_y[i] + h * f(last_x[i], last_y[i])) for i in range(1, size)])
    dY = abs(dY)
    return dY.max()

if __name__ == "__main__":
    main()
