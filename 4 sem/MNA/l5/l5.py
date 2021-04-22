import numpy as np
import scipy as sp
from scipy import linalg
from numpy import array,identity,diagonal
from math import sqrt
from data import *

def sum_of_nondiag(a, n):
    s = 0
    for i in range(n):
        for j in range(n):
            if i == j:
                continue
            s  += np.abs(a[i][j])
    return s

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
    return m, k, l

def jacobi(a, fr):
    def rotate(a,p,k,l):
        n = len(a)
        aDiff = a[l][l] - a[k][k]
        if abs(a[k][l]) < abs(aDiff)*fr: 
            t = a[k][l]/aDiff
        else:
            phi = aDiff/(2.0*a[k][l])
            t = 1.0/(abs(phi) + sqrt(phi*phi + 1.0))
            if phi < 0.0: 
                t = -t
        c = 1.0/sqrt(t**2 + 1.0)
        s = t*c
        tau = s/(1.0 + c)
        temp = a[k][l]
        a[k][l] = 0.0
        a[k][k] = a[k][k] - t*temp
        a[l][l] = a[l][l] + t*temp
        for i in range(k):
            temp = a[i][k]
            a[i][k] = temp - s*(a[i][l] + tau*temp)
            a[i][l] = a[i][l] + s*(temp - tau*a[i][l])
        for i in range(k+1,l):
            temp = a[k][i]
            a[k][i] = temp - s*(a[i][l] + tau*a[k][i])
            a[i][l] = a[i][l] + s*(temp - tau*a[i][l])
        for i in range(l+1,n):
            temp = a[k][i]
            a[k][i] = temp - s*(a[l][i] + tau*temp)
            a[l][i] = a[l][i] + s*(temp - tau*a[l][i])
        for i in range(n):
            temp = p[i][k]
            p[i][k] = temp - s*(p[i][l] + tau*p[i][k])
            p[i][l] = p[i][l] + s*(temp - tau*p[i][l])
        
    n = len(a)
    maxRot = 5*(n*n)
    p = identity(n)
    for _ in range(maxRot):
        s = sum_of_nondiag(a, n)
        m, k, l = maxElem(a)
        if abs(m) < fr:#s < fr
            p = list(p)
            for i in range(len(p)):
                for j in range(len(p[i])):
                    p[i][j] = round(p[i][j], 4)
            d = list(diagonal(a))
            for i in range(len(d)):
                d[i] = round(d[i], 4)
            v = np.array([np.array([p[i][j] for i in range(n)]) for j in range(n)])
            return d, v
        rotate(a,p,k,l)
    print ('Jacobi method did not converge')

a = A

an = np.array(a)
print(f'a =\n{an}')

res = jacobi(a, fr)

print('\n')

print(f'values:\n\t{list(res[0])}')
print(f'vectors:')
for i in res[1]:
    print(f'\t{list(i)}')

print('\n')

for i in res[1]:
    r = an.dot(np.transpose(i))
    print(f'\na*{i} = {r} = {round(r[0]/i[0], 4)}*{i}')
    # print(f'\na*{i} = {r}')
