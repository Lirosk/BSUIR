from functools import reduce
import logging

n, k = map(int, input().split())

nums = list(map(int, input().split()))
nums.sort()

if k == 1:
    print(int(num[-1] % (1e9+7)))
    exit()
if k == n:
    print(int(reduce(int.__mul__, nums[:]) % (1e9+7)))
    exit()

res = reduce(int.__mul__, nums[-k:])

l = 1
r = 1 - k

while r != 1:
    if l != n:
        b = reduce(int.__mul__, nums[:l])
    if r:
        b *= reduce(int.__mul__, nums[r:])

    if b > res:
        res = b
    
    r += 1
    l += 1
    if r == n:
        r = 0

print(int(res % (1e9+7)))
