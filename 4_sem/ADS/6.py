n, m = map(int, input().split())

res = [0] * n
a = {}

for _ in range(m):
    i, j, v = map(int, input().split())
    i -= 1

    if v not in a:
        a[v] = set(range(i, j))
    else:
        a[v].update(set(range(i, j)))
    
    print(a)

