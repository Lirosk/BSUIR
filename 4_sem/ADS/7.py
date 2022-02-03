n, m, x1, y1, x2, y2 = map(int, input().split())

# x1 -= 1
# y1 -= 1
# x2 -= 1
# y2 -= 1

vx = abs(x1 - x2)
vy = abs(y1 - y2)

if (vx == vy):
    print("NO")
else:
    print("YES")


# 0 0 0 0
# 2 0 0 0
# 0 0 0 0
# 0 0 1 0

# 2 0 0 0
# 0 0 0 0
# 0 0 0 0
# 0 0 0 1