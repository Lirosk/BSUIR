from functools import reduce

s = list(input())
q = int(input())

l = len(s)

inv = [0 for _ in range(l)]

for _ in range(q):
    left, right = input().split()

    left = int(left)
    right = int(right)

    if (left > right):
        left, right = right, left

    left -= 1

    inv[left] += 1
    inv[right] -= 1

for i in range(l):
    if (i > 0):
        inv[i] += inv[i - 1]
    if (inv[i] % 2 == 1):
        if s[i].isupper():
            s[i] = s[i].lower()
        else:
            s[i] = s[i].upper()

s = reduce(str.__add__, s)
print(s)