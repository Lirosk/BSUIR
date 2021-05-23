from functools import reduce

n, k = map(int, input().split())

nums = []
for i in input().split():
    nums.append(int(i))
nums.sort()

if k == 1:
    print(int(nums[-1] % (1e9+7)))
    exit()
if k == n:
    print(int(reduce(int.__mul__, nums[:]) % (1e9+7)))
    exit()

res = reduce(int.__mul__, nums[-k:])

l = 1
r = 1 - k

while r != 1:
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