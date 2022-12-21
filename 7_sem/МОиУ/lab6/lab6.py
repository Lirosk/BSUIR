import numpy as np

test_cases = [
    [
        A := [
            [1, 0, 2, 1],
            [0, 1, -1, 2]
        ],
        b := [2, 3],
        c := [-8, -6, -4, -6],
        D := [
            [2, 1, 1, 0],
            [1, 1, 0, 0],
            [1, 0, 1, 0],
            [0, 0, 0, 0]
        ],
        x := [2, 3, 0, 0],
        J := [0, 1],
        J_op := J[:],
        res := [1.7, 2.4, 0, 0.3],
    ],
    [
        A := [
            [6, 6, 0],
            [3, 0, 1]
        ],
        b := [3, 1],
        c := [-1, 0, 0],
        D := [
            [4, -2, 0],
            [-2, 4, 0],
            [0, 0, 1],
        ],
        x := [0, 0.5, 1],
        J := [1, 2],
        J_op := J[:],
        res := [1/3., 1/6., 0],
    ],
    [
        A := [
            [2, 1, 0],
            [5, 0, 7]
        ],
        b := [6./5, 2],
        c := [-1, -1, 0],
        D := [
            [2, 1, 0],
            [1, 2, 0],
            [0, 0, 2],
        ],
        x := [0, 6./5, 2./7],
        J := [1, 2],
        J_op := J[:],
        res := [2./5, 2./5, 0],
    ],
    [
        A := [
            [3./2, 0, 3],
            [3, 1, 0]
        ],
        b := [1, 1],
        c := [-1, 0, 0],
        D := [
            [4, 0, -2],
            [0, 1, 0],
            [-2, 0, 4],
        ],
        x := [0, 1, 1./3],
        J := [1, 2],
        J_op := J[:],
        res := [1./3, 0, 1./6],
    ]
]

rounding = 5


def quadratic_programming_problem(A, b, c, D, x, J, J_op):
    A = np.array(A, dtype=float)
    b = np.array(b, dtype=float)
    c = np.array(c, dtype=float)
    D = np.array(D, dtype=float)
    x = np.array(x, dtype=float)
    J = np.array(J, dtype=int)
    J_op = np.array(J_op, dtype=int)

    m, n = A.shape

    while True:
        # формируем вектор c(x) = c + D*x
        cx = c + np.matmul(D, x)

        c_op = cx[J_op]
        A_op = A[:, J_op]
        A_op_inv = np.linalg.inv(A_op)

        # считаем вектор потенциалов
        ux = -np.matmul(c_op, A_op_inv)

        # вектор оценок
        deltas = np.matmul(ux, A) + cx
        deltas = np.array([round(_x, rounding) for _x in deltas])

        # проверяем условие оптимальности
        if all(deltas >= 0):
            print('План оптимальный')
            print(f'x\' = {[round(_x, rounding) for _x in x]}')
            return

        j0 = np.argmin(deltas)

        while True:
            # формируем систему
            DJ = D[J][:, J]
            AJ = A[:, J]

            Aj0 = A[:, j0]
            Dj0 = D[j0][J]

            l_len = len(J)
            y_len = m
            syst = np.zeros((l_len + y_len, l_len + y_len))

            syst[:l_len, :l_len] = DJ
            syst[l_len:, :l_len] = AJ
            syst[:l_len, l_len:] = AJ.T

            syst_b = np.zeros(l_len + y_len)
            syst_b[: l_len] = -Dj0
            syst_b[l_len: ] = -Aj0

            # получаем единственное решение
            res = np.linalg.solve(syst, syst_b)
            
            lJ = res[:l_len]
            y = res[-y_len:]

            l = np.zeros(n)
            l[J] = lJ

            # строим новый план
            delta = np.matmul(Dj0, lJ) + np.matmul(Aj0, y) + D[j0][j0]
            theta_j0 = abs(deltas[j0] / delta) if delta != 0 else np.inf

            thetas = [(-x[j] / l[j] if l[j] < 0 else np.inf) for j in J]

            theta0 = min(thetas)
            if theta0 == np.inf:
                print('Задача не имеет решения в силу неограниченности снизу целевой функции на множестве планов')
                return

            jJ = np.argmin(thetas)
            if thetas[jJ] >= theta_j0:
                theta0 = theta_j0
                jJ = j0
            else:
                theta0 = thetas[jJ]
                jJ = J[jJ]

            # обновляем текущий план
            x[J] += theta0 * lJ
            x[j0] += theta0

            for j in range(n):
                if j not in J and j != j0:
                    x[j] = 0

            # обновляем множество индексов J
            if j0 == jJ:
                J = np.append(J, [j0])
            elif (jJ in J) and (jJ not in J_op):
                J = [j for j in J if j != jJ]
                deltas[j0] += theta0 * delta
                continue
            else:
                s = np.where(J_op == jJ)
                es = np.eye(m)[s]
                j_plus = np.array(set(J) - set(J_op))

                if j_plus and any(es.dot(A_op_inv).dot(A[:, j_plus]) != 0):
                    J = J[J != jJ]
                    J_op = np.append(J_op[J_op != jJ], j_plus)
                    deltas[j0] += theta0 * delta
                    continue
                else:
                    J = np.append(J[J != jJ], j0)
                    J_op = np.append(J_op[J_op != jJ], j0)

            J.sort()
            J_op.sort()

            break    


for *data, res in test_cases:
    quadratic_programming_problem(*data)
    print(f'Правильный ответ:\nx\' = {[round(_x, rounding) for _x in res]}\n\n')