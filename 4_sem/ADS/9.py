from functools import reduce

s = list(input())
q = int(input())

l = len(s)

b = [False] * l

for _ in range(q):
    left, right = input().split()
    left = int(left) - 1
    right = int(right)

    for i in range(left, right):
        b[i] = not b[i]

for i in range(l):
    if b[i]:
        if s[i].isupper():
            s[i] = s[i].lower()
        else:
            s[i] = s[i].upper()

s = reduce(str.__add__, s)
print(s)