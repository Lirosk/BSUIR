n = input()
n = int(n)
l = len(n)
ns = str(n)

i, j = 0, 0
max = l[-1]

for k in range(1, l):
    if max < l[k]:
        max = l[k]
        i = k
    elif max > l[k]:
        j = k



