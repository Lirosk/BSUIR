s = list(input())
l = len(s)

pol = True
for i in range(1,l):
    if (s[0] != s[i]):
        pol = False
        break

if pol:
    print(-1)
else:
    pol = True
    for i in range(l//2):
        if (s[i] != s[l-1-i]):
            pol = False
            break

    if pol:
        print(l-1)
    else:
        print(l)
