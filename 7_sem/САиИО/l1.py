from numbers import Integral
import math
import copy
from math import inf

def dual_simplex_max(A, Jb, c, a, b):
    while not all(i >= 0 for i in b):
        index_min_row = min(range(len(b)), key=b.__getitem__)
        c = [-i for i in c]
        min_v = inf
        index_min_column = -1
        for i in range(len(A[0])):
            if A[index_min_row][i] < 0 and abs(c[i] / A[index_min_row][i]) < min_v:
                min_v = abs(c[i] / A[index_min_row][i])
                index_min_column = i
        if index_min_column == -1:
            return None
        min_v = A[index_min_row][index_min_column]
        for i in range(len(A[0])):
            A[index_min_row][i] = A[index_min_row][i] / min_v
        b[index_min_row] = b[index_min_row] / min_v
        for i in range(len(A)):
            if i == index_min_row:
                continue
            value = -A[i][index_min_column]
            b[i] = b[index_min_row] * value + b[i]
            for j in range(len(A[0])):
                A[i][j] = A[index_min_row][j] * value + A[i][j]
        value = -c[index_min_column]
        for i in range(len(c)):
            c[i] = A[index_min_row][i] * value + c[i]
        Jb[index_min_row] = index_min_column
    x = [0 for _ in range(len(A[0]))]
    for i, j in zip(Jb, b):
        x[i] = j
    return x

def get_float_xi(x, n):
    for i in range(n):
        if not isinstance(x[i], Integral):
            return x[i], i

def branch_and_bound_method(i_c, i_A, i_b, i_d_minus, i_d_plus):
    u_c = copy.deepcopy(i_c)
    u_A = copy.deepcopy(i_A)
    u_b = copy.deepcopy(i_b)
    u_d_minus = copy.deepcopy(i_d_minus)
    u_d_plus = copy.deepcopy(i_d_plus)
    n = len(u_c)
    m = len(u_b)
    
    for i in range(0, n):
        if u_c[i] > 0:
            u_c[i] = u_c[i] * (-1)
            for j in range(0, m):
                u_A[j][i] = u_A[j][i] * (-1)
            u_d_plus[i] = u_d_plus[i] * (-1)
            u_d_minus[i] = u_d_minus[i] * (-1)
            u_d_plus[i], u_d_minus[i] = u_d_minus[i], u_d_plus[i]
    
    a = 0
    c = [0 for _ in range(2 * n + m)]
    for i in range(n):
        c[i] = u_c[i]
    A = [[0 for _ in range(2 * n + m)] for _ in range(m + n)]
    for i in range(m):
        for j in range(n):
            A[i][j] = u_A[i][j]
    for i in range(n):
        for j in range(n):
            if i == j:
                A[i + m][j] = 1
    for i in range(m + n):
        for j in range(m + n):
            if i == j:
                A[i][j + n] = 1
    b = [0 for _ in range(n + m)]
    for i in range(m):
        b[i] = u_b[i]
    for i in range(m, n + m):
        b[i] = u_d_plus[i - m]
    d_minus = [0 for _ in range(2 * n + m)]
    for i in range(n):
        d_minus[i] = u_d_minus[i]
    
    s = []
    X = None
    r = None
    s.append(Stack(c, a, A, b, d_minus, d_minus))
    
    while len(s) != 0:
        i = len(s) - 1
        c = s[i].c
        a = s[i].alfa
        A = s[i].A
        b = s[i].b
        d_minus = s[i].d_minus
        delta = s[i].delta
        s.remove(s[i])
        if not all(d == 0 for d in d_minus):
            result = 0
            for i1, i2 in zip(c, d_minus):
                result += i1 * i2
            a2 = a + result
            result = [0 for _ in range(len(A))]
            for i in range(len(A)):
                for j in range(len(A[0])):
                    result[i] += A[i][j] * d_minus[j]
            b2 = [i1 - i2 for i1, i2 in zip(b, result)]
        else:
            a2 = a
            b2 = b
        y = [0 for _ in range(m + n)]
        B = [n + i for i in range(1, n + m + 1)]
        Jb = [i - 1 for i in B]
        x = dual_simplex_max(copy.deepcopy(A), Jb.copy(),
        c.copy(), a2, b2.copy())
        
        if all(isinstance(i, Integral) for i in x):
            x_plan = [i + j for i, j in zip(x, delta)]
            k = sum([i*j for i, j in zip(c, x_plan)]) + a2
            if X is None or k > r:
                X = x_plan
                r = k
        else:
            xi, xi_index = get_float_xi(x, n)
            k = math.floor(sum([i*j for i, j in zip(c, x)]) + a2)
            if X is None or k > r:
                b3 = b2.copy()
                b3[m + xi_index] = math.floor(xi)
                d_minus_zero = [0 for _ in d_minus]
                d_minus = [0 for _ in range(2 * n + m)]
                d_minus[xi_index] = math.ceil(xi)
                s.append(Stack(c, a2, A, b3, d_minus_zero, delta))
                delta = [i + j for i, j in zip(delta, d_minus)]
                s.append(Stack(c, a2, A, b2, d_minus, delta))
    if X is None:
        print("Задача несовместна")
        return None
    else:
        x = [0 for _ in range(n)]
        for i in range(n):
            if i_c[i] < 0:
                x[i] = X[i]
            else:
                x[i] = -X[i]
        return x

class Stack:
    def __init__(self, c, alfa, A, b, d_minus, delta) -> None:
        self.c = c
        self.alfa = alfa
        self.A = A
        self.b = b
        self.d_minus = d_minus
        self.delta = delta

if __name__ == "__main__":
    c = [4, 1]
    A = [
        [1, 2],
        [3, 2]
    ]
    b = [4, 12]
    d_minus = [0, 0]
    d_plus = [3, 3]
    result = branch_and_bound_method(c, A, b, d_minus, d_plus)
    if result == None:
        print("Задача несовместна")
    else:
        print(f"Оптимальный план: {tuple(result)}")