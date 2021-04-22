data = __import__("data")

from sympy import plot_implicit
import sympy as sp
import math
import symbol

def main():
    print(f"\nsystem:\n{data.ne1} = {data.ne1a}\n{data.ne2} = {data.ne2a}\n")
    
    pf()
    
    print(separate_roots(data.m[0] - data.m[1], -10, 10, 0.5))

    x0 = list(map(lambda n: float(n), input("Enter x0, y0:\n").replace(",", " ").split()))
    print()

    sim(x0)
    nm(x0)

def pf():
    p = plot_implicit(data.m[0], line_color = "green", show = False)
    p.extend(plot_implicit(data.m[1], line_color = "cyan", show = False))
    p.show()


def nm(x0: list) -> None:
    x = x0.copy()
    pre_x: list = [n - 2*data.fr for n in x]
    lim: int = 1e3
    iters: int = 0

    while (iters < lim) and not (max([abs(x[0] - pre_x[0]), abs(x[1] - pre_x[1])]) < data.fr):
        pre_x = x.copy()

        '''
        x[0] = float(data.f1(pre_x) + (data.j[0].subs({data.abc.x: pre_x[0], data.abc.y: pre_x[1]}) + data.j[1].subs({data.abc.x: pre_x[0], data.abc.y: pre_x[1]})))
        x[1] = float(data.f2(pre_x) + (data.j[2].subs({data.abc.x: pre_x[0], data.abc.y: pre_x[1]}) + data.j[3].subs({data.abc.x: pre_x[0], data.abc.y: pre_x[1]})))
        '''

        x[0], x[1] = data.fnm(pre_x)

        iters += 1

    if (iters == lim):
        print("Iteration sequence does not converge for newtone method...\n")
        return

    print(iters)
    res = [round(i, int(-math.log10(data.fr))) for i in x]
    print(res)


def sim(x0: list) -> None:
    x = x0.copy()
    pre_x = [n - 2*data.fr for n in x]
    iters: int = 0
    lim: int = 1e3

    while (iters < lim) and not (max([abs(x[0] - pre_x[0]), abs(x[1] - pre_x[1])]) < data.fr):
        pre_x = x.copy()

        x[0] = float(data.phi1(pre_x))
        x[1] = float(data.phi2(pre_x))

        iters += 1

    if (iters == lim):
        print("Iteration sequence does not converge for simple iterations method...\n")
        return

    print(iters)
    res = [round(i, int(-math.log10(data.fr))) for i in x]
    print(res)

def separate_roots(f0, x1: float, x2: float, dx: float) -> [list]:
    dx = abs(dx)

    pre_x = x1
    x: float = x1 + dx

    l: float = f0.subs({"x": pre_x, "y": 0})
    t: float = 0

    sections: [list] = []

    while (abs(x - x2) > dx/2):
        t = f0.subs({"x": x, "y": 0})

        if (l*t < 0):
            sections.append([pre_x, x])
        elif (l*t == 0):
            if (t == 0):
                sections.append([x, x])
        
        l = t
        pre_x = x

        x += dx

    return sections

if __name__ == "__main__":
    main()
