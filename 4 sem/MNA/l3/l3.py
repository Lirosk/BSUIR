from numpy import sign, linspace
from data import *
from typing import List
from polynomial import *

import matplotlib.pyplot as plt


def main() -> None:
    global f0

    if (input("Do u wanna to set ur own coefficients?('y' if yes): ").strip().lower() == "y"):
        i: int = 0
        coefs: list = []

        print("Press <Enter> to end the input.\n")
        while True:
            try:
                buf = input(f"Enter coef for {i} degree: ")
                if (buf == ""):
                    print("end of input.\n")
                    break

                coef = float(buf)
            except ValueError:
                print("invalid value...\n\n")
                continue
            
            i += 1
            coefs.append(coef)

        f0 = Polynomial(coefs)
    else:
        f0 = Polynomial([C, B, A, 1])    
    f: list = []
    #f.append(f0)

    #f.append(Polynomial([0, -131681894400, 0, 202759531776, 0, -84865562640, 0, 15088541896, 0, -1367593305, 0, 68943381, 0, -1999370, 0, 32946, 0, -285, 0, 1]))
    # integers from [-9, 9]

    f.append(Polynomial([1, 0, -4.453, 0, 0.5e-8, 1]))
    # [-0.4640905482, 0.4747946807, 1.607794419]

    #f.append(Polynomial([0, 0, 1]))
    # [0]

    f.append(Polynomial([1, 0, 1]))
    # no real roots

    f.append(Polynomial([3, 0, 0, 0, 0, 0, 0, 0, -2.4, -9.21651, 0.16546]))
    # [0.8582756483]

    for func in f:
        f0 = func

        print(f"\n\ncoefs: {f0.coefficients}")

        task1()
        sections = task2()
        task3(sections, fr)


def task3(sections: List[list], fr: float) -> None:
    if not sections:
        print("\n\nNo real roots")
        return [None]

    def half_division_method() -> list:
        c: float = 0
        a: float = 0
        b: float = 0

        answers: list = []
        iters: list = []


        for i in sections:
            a = i[0]
            b = i[1]

            iter: int = 0

            if (a == b):
                answers.append(a)
                iters.append(0)
                continue

            while not (abs(b - a) < fr):
                c = (a + b) / 2

                if (sign(f0.subs(a)) == sign(f0.subs(c))):
                    a = c
                else:
                    b = c

                iter += 1

            iters.append(iter)
            answers.append(c) 

        print(f"iterations for half_division_method: {iters} or {sum(iters)}")
        return answers

    
    def chord_method() -> list:
        answers: list = []  
        iters: list = []      

        for i in sections:
            x: float = i[0]
            pre_x: float = x + 2*fr

            iter: int = 0

            if (i[0] == i[1]):
                answers.append(i[0])
                iters.append(0)
                continue

            lim = 1e3

            done: bool = False

            if (f0.subs(i[1])*f0.diff().diff().subs(i[1]) > 0):
                fka = lambda n: n - f0.subs(n)*(i[1] - n)/(f0.subs(i[1]) - f0.subs(n))
                x = i[0]
            elif (f0.subs(i[0])*f0.diff().diff().subs(i[0]) > 0):
                fka = lambda n: n - f0.subs(n)*(i[0] - n)/(f0.subs(i[0]) - f0.subs(n))
                x = i[1]
            else:
                a = i[0]
                b = i[1]
                
                while not (abs(b - a) < fr) and lim > 0:
                    a = b - (b - a) * f0.subs(b) / (f0.subs(b) - f0.subs(a))
                    b = a - (a - b) * f0.subs(a) / (f0.subs(a) - f0.subs(b))                              

                    lim -= 1
                    iter += 1

                x = b
                done = True
                
            while not done and not (abs(x - pre_x) < fr) and lim > 0:
                pre_x = x
                x = fka(x)

                lim -= 1
                iter += 1

            iters.append(iter)
            answers.append(x)

        print(f"iterations for chord_method: {iters} or {sum(iters)}")
        return answers


    def newton_method() -> list:
        f1 = f0.diff()

        answers: list = []
        iters: list = []

        for i in sections:
            if (i[0] == i[1]):
                answers.append(i[0])
                iters.append(0)
                continue

            iter: int = 0

            

            if (f0.subs(i[0])*f1.diff().subs(i[0]) > 0):
                x = i[0]
            elif (f0.subs(i[1])*f1.diff().subs(i[1]) > 0):
                x = i[1]
            else:
                x = (i[0] + i[1])/2

            pre_x = x + 2 * fr
            lim = 1e3
        
            counter: int = 1

            while not (abs(x - pre_x) < fr) and lim > 0:
                pre_x = x

                if (f1.subs(x) == 0):
                    x = i[0] + counter*fr
                    pre_x = x + fr * 2

                    counter += 1

                    if (x >= i[1]):
                        x = None
                        break

                    continue

                x = pre_x - f0.subs(pre_x)/f1.subs(pre_x)
                lim -= 1
                iter += 1

            iters.append(iter)
            answers.append(x)

        print(f"iterations for newton_method: {iters} or {sum(iters)}")
        return answers


    methods = [half_division_method, chord_method, newton_method]

    print("\n\nanswers: \n")
    for m in methods:
        answer = m()
        print(answer, "\n")

    print("\n\n\n")


def task2() -> List[list]:
    def separate_roots(dx: float) -> List[list]:
        dx = abs(dx)

        pre_x = x1
        x: float = x1 + dx

        l: float = f0.subs(x1)
        t: float = 0

        sections: List[list] = []

        while (abs(x - x2) > dx/2):
            t = f0.subs(x)

            if (l*t < 0):
                sections.append([pre_x, x])
            elif (l*t == 0):
                if (t == 0):
                    sections.append([x, x])
                else:
                    sections.append([pre_x, pre_x])
            
            l = t
            pre_x = x

            x += dx

        return sections

    plot_show()

    sections = separate_roots(1)
    return sections


def plot_show() -> None:
    if (input("U wanna see the plot?('y' if yes): ").lower().strip() == "y"):

        lines_color = "gray"
        plt.axhline(0, color = lines_color)
        plt.axvline(0, color = lines_color)
        
        plt.xlabel("x")
        plt.ylabel("y")

        plt.ylim(top = x2/2, bottom = x1/2)

        xp = linspace(x1, x2, 100)
        fp = 0

        for i in range(f0.degree + 1):
            fp += f0[i]*xp**i

        plt.plot(xp, fp, 'r')
        plt.show()


def task1() -> None:
    f: list = [f0]

    i: int = 0
    while True:
        f.append(f[i].diff())
        i += 1

        if f[i].degree == 0:
            break

    arr: list = []

    for i in range(len(f)):
        arr.append(
            list(map(
                lambda x: sign(x),
                [f[i].subs(x1), f[i].subs(x2)]
            ))
        )

    a: int = 0
    b: int = 0
    for i in range(len(arr) - 1):
        if (arr[i][0] != arr[i + 1][0]):
            a += 1
        if (arr[i][1] != arr[i + 1][1]):
            b += 1

    n = a - b

    print(f"Number of roots: {n}\n")


if __name__ == "__main__":
    main()