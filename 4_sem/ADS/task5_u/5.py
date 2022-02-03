n = int(input())
m = int(input())

r = []

for i in range(n):
    l = [0]*n
    r.append(l)

for _ in range(m):
    i, j, w = list(map(int, input().split()))

    i -= 1
    j -= 1

    if not r[i][j] or r[i][j] > w:
        r[i][j] = w
        r[j][i] = w

_i = int(input()) - 1
_j = int(input()) - 1

if _i == _j:
    print(0)
    exit()

pull = [[], []]

def get_connected(i):
    for j in range(n):
        if i != j and r[i][j]:
            yield (i, j)

for i in get_connected(_i):
    pull[0].append(i)

# w = [False]*n
d = [0]*n

while pull[0]:
    for i, j in pull[0]:
        # w[i] = True
        # w[j] = True
        b = d[i] + r[i][j]

        if (not d[j] or d[j] > b) and j != _i:
            d[j] = b
            for k in get_connected(j):
                if k[1] != i and k[1] != _i:
                    pull[1].append(k)
    
    pull.pop(0)
    pull.append([])

print(d[_j])

'''
6
7
1 3 5
4 2 2
3 6 8
1 5 1
4 5 1
3 4 10
2 3 7
3
5
'''