from math import inf


def ford_falkerson(V, a, s, t):
    ra = {(i[1], i[0]): 0 for i in a}
    f = a.copy() | ra.copy()
    for i in f:
        f[i] = 0
    sup_arcs = a | ra
    for i in a:
        sup_arcs[i] = a[i] - f[i] + f[(i[1], i[0])]
        sup_arcs[(i[1], i[0])] = ra[(i[1], i[0])] - f[(i[1], i[0])] + f[i]
    while True:
        labels = {i: None for i in V}
        labels[s] = 0
        q = [s]
        while len(q) != 0:
            point = q.pop(0)
            out_arcs = {i: sup_arcs[i]
                        for i in sup_arcs
                        if sup_arcs[i] != 0 and i[0] == point}
            for i in out_arcs:
                if labels[i[1]] == None:
                    labels[i[1]] = i
                    q.append(i[1])
            if t in q:
                break
            if len(q) == 0:
                # STOP
                f = {i: f[i] for i in f if i in a}
                max_flow = sum(f[i] for i in f if i[0] == s)
                return f, max_flow
        path = []
        path.append(t)
        while path[len(path) - 1] != s:
            point = path[len(path) - 1]
            path.append(labels[point][0])
        path.reverse()
        teta = inf
        for i in range(1, len(path)):
            if sup_arcs[(path[i - 1], path[i])] < teta:
                teta = sup_arcs[(path[i - 1], path[i])]
        for i in range(1, len(path)):
            f[(path[i - 1], path[i])] += teta
            sup_arcs[(path[i - 1], path[i])] -= teta
            sup_arcs[(path[i], path[i - 1])] += teta


if __name__ == '__main__':
    V = [
        1, 2, 3, 4
    ]
    a = {
        (1, 2): 1,
        (1, 3): 1,
        (2, 3): 2,
        (2, 4): 2,
        (3, 4): 3,
    }
    s = 1
    t = 4
    f, max_flow = ford_falkerson(V, a, s, t)
    print("Результат:", f)
    print("Максимальный поток: ", max_flow)
