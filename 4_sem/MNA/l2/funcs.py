import numpy as np
from data import FR


#########################

def AppendToRows(A, b):
    A = A.tolist()
    for row in range(l):
        A[row].append(float(b[row]))


#########################

def preparations(A, b):
    if (type(A) != type(np.array([]))):
        A = np.array(A)
    if (type(b) != type(A)):
        b = np.array(b)


#########################

def checkingAndPreparations(A, b):
    if not NoZeroMainDiag(A):
        print("Zeros on main diag\n\n")
        exit(1)

    alpha, beta = otherView(A, b) 
    if not ifConvergent(alpha):
        diagSupremacy(A, b)
        alpha, beta = otherView(A, b) 
        if not ifConvergent(alpha):
            print("Matrix is not convergent\n\n")
            exit(2)

    return alpha, beta

#########################

def otherView(A, b):
    alpha = np.array(A)
    beta = b.copy()

    for i in range(l):
        alpha[i] /= A[i][i]
        beta[i] /= A[i][i]
    alpha = np.eye(l) - alpha

    return alpha, beta

#########################

def sImPlEiTeRaTiOnSmeThoD(A, b):
    preparations(A, b)
    alpha, beta = checkingAndPreparations(A, b)

    vars = beta.copy()
    iter = 0
    while True:
        temp = [0.] * l
        # vars = (beta - alpha * vars)[0] #shame
        for i in range(l):
            for j in range(l):
                temp[i] += alpha[i][j] * vars[j]
            temp[i] += beta[i]

        if sum([round(abs(vars[i] - temp[i]), FR) for i in range(l)]) == 0:
            temp = list(map(lambda x: round(x, FR), temp))
            print("sImPlEiTeRaTiOnSmeThoD iters: ", iter)
            return temp.copy()

        vars = temp.copy()
        iter += 1


#########################

def makeTriags(A):
    H = [] # bottom
    F = [] # roof
    for i in range(l):
        F.append([A[i][j] if (j >= i) else 0 for j in range(l)])
        H.append([A[i][j] if (j < i) else 0 for j in range(l)])

    return H, F


#########################

def gAuSsSeIdeLmEtHoD(A, b):
    preparations(A, b)
    alpha, beta = checkingAndPreparations(A, b)
    

    H, F = list(map(lambda x: np.array(x), makeTriags(alpha)))

    prevars = [0.] * l
    vars = beta.copy()

    iters = 0

    while True:
        temp = [0.] * l
        # vars = (beta - alpha * vars)[0] #shame
        for i in range(l):
            for j in range(l):
                temp[i] += H[i][j] * vars[j] + F[i][j] * prevars[j]
            temp[i] += beta[i]

        if sum([round(abs(vars[i] - temp[i]), FR) for i in range(l)]) == 0:
            temp = list(map(lambda x: round(x, FR), temp))
            print("gAuSsSeIdeLmEtHoD iters: ", iters)
            return temp.copy()

        prevars = vars.copy()
        vars = temp.copy()

        iters += 1


#########################

def NoZeroMainDiag(A):
    global l
    l = len(A)

    for i in range(0, l):
        if (A[i][i] == 0):
            return False
    return True


#########################

def swap(A, B):
    temp = A.copy()
    A = B.copy()
    B = temp


#########################

def diagSupremacy(A, B):
    for i in range(len(A) - 1):
        max = abs(A[i][i])
        for j in range(i + 1, len(A)):
            if max < abs(A[j][i]):
                swap(A[i], A[j])
                B[i], B[j] = B[j], B[i]


#########################

def ifConvergent(A):
    norm = np.linalg.norm(A)
    if norm < 1:
        return True

    eigen = np.linalg.eig(A)[0]
    for i in eigen:
        if not abs(i) < 1:
            return False

    return True


#########################
