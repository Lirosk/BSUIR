def ins(l1, l2):
    res = []
    l = min(len(l1), len(l2))
    i = 0
    while i < l:
        if l1[i] == l2[i]:
            res.append(l1[i])
        i += 1 
    return res

N = int(input())
num = list(map(lambda x: int(x), input().split()))

c = num[:]
num.sort()
i = ins(c, num)

print((N - len(i))/2)