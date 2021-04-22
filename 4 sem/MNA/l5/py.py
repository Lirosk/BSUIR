import numpy as np

def maxElem(a):
    n = len(a)

    k, l = 0, 1
    m = a[k][l]
    
    for i in range(n-1):
        for j in range(i+1,n):
            if abs(a[i][j]) >= m:
                m = abs(a[i][j])
                k = i
                l = j
    return k, l

def sum_of_nondiag(a, n):
    s = 0
    for i in range(n):
        for j in range(n):
            if i == j:
                continue
            s  += np.abs(a[i][j])
    return s

def rot_m(n, i, j, theta):
    m = np.eye(n)
    m[i][i] = np.cos(theta)
    m[j][j] = np.cos(theta)
    m[i][j] = -np.sin(theta)
    m[j][i] = np.sin(theta)
    return m

def jacobi(a, n, i, j):
    '''
    p = 2*a[i][j]/(a[i][i] - a[j][j])
    c = 1/np.sqrt(2*(1 + (1 + p*p)))
    s = np.sign(p)/np.sqrt(2*(1-(1+p*p)))

    b  = [[0]*n]*n

    for k in range(1, n):
        b[k][i] = a[k][i]*c+a[k][j]*s
        b[k][j] = -a[k][i]*s+a[k][j]*c

    for k in range(1, n):
        a[i][k] = b[i][k]*c+b[j][k]*s
        a[j][k] = -b[i][k]*s+b[j][k]*c

    return a, b
    '''
    if a[i][i] == a[j][j]:
        theta = np.pi/4
        r = rot_m(n, i, j, theta)
    else:
        theta = (a[i][i]-a[j][j])/2/a[i][j]
        t = np.sign(theta)/(np.abs(theta) + np.sqrt(1+theta*theta))
        c = 1/np.sqrt(1+t*t)
        s = c*t

        r = np.eye(n)
        r[i][i] = c
        r[j][j] = c
        r[i][j] = -s
        r[j][i] = s

    a = np.linalg.inv(r)*a*r
    return a

fr = 1e-4
A = [
    [2, 1],
    [1, 2]
]

n = len(A)
A = np.array(A)

print(np.linalg.eig(A))

while sum_of_nondiag(A, n) >= fr:
    i, j = maxElem(A)
    A = jacobi(A, n, i, j)

print(A)