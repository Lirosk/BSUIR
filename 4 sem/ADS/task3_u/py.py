import random as r

n = 10
k = 10 # r.randrange(1, 11)

l = []
for i in range(n):
    l.append(r.randrange(0, 25))

print(f"{n} {k}")
print(*l)
