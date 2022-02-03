n = input()
nums = list(map(int, input().split()))

res = 0
mx = nums[0]
last = None

for i in nums:
    if last is not None:
        if last > i:
            res += last - i
        if i > mx:
            res += i - mx
            mx = i
    last = i

print(res)
