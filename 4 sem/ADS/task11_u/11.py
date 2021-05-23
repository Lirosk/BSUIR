n = int(input())

i, j, k = 0, 0, 0

r = []
while i < n:
    r.append([])
    j = 0
    while j < n:
        r[i].append(0)
        j += 1
    i += 1

c = 0
while c < n-1:
    i, j, k = input().split()
    c += 1
    i = int(i) - 1
    j = int(j) - 1
    k = int(k)

    r[i][j] = k
    r[j][i] = k

res = 0
for i in r:
    res += sum(i)

print(int((res * 2) % (1e7 + 7)))