s = input()
l = len(s)

if (l == 1):
    print(-1)
    exit(0)

palindrome = True
for i in s:
    if (i != s[0]):
        palindrome = False
        break

if (palindrome):
    print(-1)
    exit(0)

palindrome = True
for i in range(l//2):
    if s[i] != s[-i-1]:
        palindrome = False
        break

if (palindrome):
    print(((l - 1) if (l != 1) else (-1)))
else:
    print(l)
    