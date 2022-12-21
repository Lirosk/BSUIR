import numpy as np
from l5 import max_matching


def assignment_problem(c):
    a = [0] * len(c)
    b = [0] * len(c)
    for i in range(len(b)):
        b[i] = min(np.array(c)[0:len(c), i])
    V1 = [f'x{i}' for i in range(len(c))]
    V2 = [f'y{i}' for i in range(len(c))]
    while True:
        J_equal = []
        for i in range(len(c)):
            for j in range(len(c)):
                if a[i] + b[j] == c[i][j]:
                    J_equal.append([f'x{i}', f'y{j}'])
        M = max_matching(V1, V2, J_equal.copy())
        # print(M)
        if (len(M) == len(c)):
            # STOP
            result = []
            for i in M:
                result.append([int(i[0][1]) + 1, int(i[1][1]) + 1])
            return result
        A = []
        for i in J_equal:
            if (i in M):
                A.append([i[1], i[0]])
            else:
                A.append(i)
        start = V1.copy()
        for i in M:
            if i[0] in start:
                start.remove(i[0])
        I_star = start.copy()
        J_star = []
        V = V1 + V2
        labels = {i: None for i in V}
        for i in start:
            labels[i] = -1  # star
        Q = start.copy()
        while len(Q) != 0:
            point = Q.pop(0)
            out_arcs = [i for i in A if i[0] == point]
            for i in out_arcs:
                if labels[i[1]] == None:
                    labels[i[1]] = -1
                    Q.append(i[1])
                    if i[1][0] == 'x':
                        I_star.append(i[1])
                    else:
                        J_star.append(i[1])
        _a = [-1] * len(a)
        _b = [1] * len(b)
        for i in I_star:
            _a[int(i[1])] = 1
        for j in J_star:
            _b[int(j[1])] = -1
        teta = min(
            [(c[int(i[1])][int(j[1])] - a[int(i[1])] -
             b[int(j[1])]) / 2
             for i in I_star
             for j in V2 if j not in J_star
             ]
        )
        for i in range(len(a)):
            a[i] = a[i] + teta * _a[i]
        for i in range(len(b)):
            b[i] = b[i] + teta * _b[i]


if __name__ == '__main__':
    c = np.array([
        [7, 2, 1, 9, 4],
        [9, 6, 9, 5, 5],
        [3, 8, 3, 1, 8],
        [7, 9, 4, 2, 2],
        [8, 4, 7, 4, 8],
    ])
    print("C:")
    print(c)
    result = assignment_problem(c.copy())
    print("Результат:", result)
    c = np.array([
        [50, 19, 22, 24],
        [23, 21, 23, 20],
        [18, 21, 23, 33],
        [19, 17, 15, 24]
    ])
    print()
    print("C:")
    print(c)
    result = assignment_problem(c.copy())
    print("Результат:", result)
    c = np.array([
        [4, 2, 4],
        [3, 1, 2],
        [4, 4, 4]
    ])
    print()
    print("C:")
    print(c)
    result = assignment_problem(c.copy())
    print("Результат:", result)
