n = int(input())
nums = list(map(int, input().split()))

mx = nums[0]
res = 0

for i in range(1, n):
    if (nums[i] > mx):
        res += nums[i] - mx
        mx = nums[i]
    elif nums[i - 1] > nums[i]:
        res += nums[i - 1] - nums[i]

print(res)