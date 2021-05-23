from functools import reduce

n = list(map(int, str(int(input()))))
l = len(n)

def find(s, f, cn):
    if f <= s:
        return None, None

    # find max
    res = n[s]
    pos = s
    for i in range(s + 1, f):
        if (res < n[i]):
            res = n[i]
            pos = i

    # find min
    for i in range(s, f):
        if (n[i] < res and n[i] > cn):
            res = n[i]
            pos = i

    return res, pos

done = False
for i in range(1, len(n)):
    exch, pos = find(l-i, l, n[-i-1])
    if (exch is not None) and (exch > n[-i-1]):
        n[-i-1], n[pos] = n[pos], n[-i-1]
        done = True
        n = n[:-i] + sorted(n[-i:])
        break

if done:
    print(
        int(
            reduce(str.__add__, [str(i) for i in n])
            )
        )
else:
    print(-1)
