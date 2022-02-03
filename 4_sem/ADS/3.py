from functools import reduce
import random

def main():
    N, K = input().split()
    N = int(N)
    K = int(K)

    s = input().split()
    s = list(map(int, s))
    # s = []
    # for i in range(N):
    #     s.append(random.randrange(-N//2, N//2))
        
    

    l = []
    m = 1

    for i in range(K):
        m *= s[i]

    # print(s)
    for i in s:
        l.append(i)
        if len(l) == K + 1:
            l.pop(0)
            # print(l)
            n = reduce(int.__mul__, l)
            if n > m:
                m = n

    m %= (1e9 + 7)
    print(int(m))


if __name__ == '__main__':
    main()
    
'''
-5 -4 -3 2 3 4, k = 2
-5 -4
-5 4
3 4
'''
