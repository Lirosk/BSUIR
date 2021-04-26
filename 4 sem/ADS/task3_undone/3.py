from functools import reduce

n, k = map(int, input().split())
nums = list(map(int, input().split()))
nums.sort(key = abs)

if k == n:
    print(reduce(int.__mul__, nums))
    exit()
    
neg = 0
aneg = 0
for i in range(n):
    if nums[i] < 0:
        aneg += 1
        if i >= k-1:
            neg += 1














if neg % 2 == 0 or k == n:
    res = reduce(int.__mul__, nums[-k:])
else:
    res = 1
    neg -= 1
    nw = 0
    j = n-1
    for i in range(k):
        if nums[j] >= 0:
            res *= nums[j]
        else:
            if (nw < neg):
                res *= nums[j]
                nw += 1
            else:
                i -= 1
        j -= 1

print(res)