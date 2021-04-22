import sympy as sp
from sympy import abc
from sympy.parsing import parse_expr

A: float = 0.5
M: float = 0

fr: float = 1e-4


ne1 = f"-(x**{3}+y**{3}-3*x*y**{2}+1)"
ne1a = f"x"
ne2 = f"x"
ne2a = f"y"
'''
ne1 = f"tan(x*y + {M})"
ne1a = f"x"
ne2 = f"{A}*x**2+2*y**2 + y - 1"
ne2a = f"y"
'''


e1 = parse_expr(ne1)
e1a = parse_expr(ne1a)
e2 = parse_expr(ne2)
e2a = parse_expr(ne2a)


'''
sp.tan(abc.x*abc.y + M) - abc.x,
sp.sqrt((1-A*abc.x**2)/2) - abc.y
'''  
m = sp.Matrix([
        e1 - e1a, 
        e2 - e2a
    ])
symbs = sp.Matrix([abc.x, abc.y])

j = (m.jacobian(symbs))**(-1)


def f1(vars: list) -> float:
    return (e1 - e1a).subs({"x": vars[0], "y": vars[1]})
    '''return (sp.tan(vars[0] * vars[1] + M) - vars[0])'''

def f2(vars: list) -> float:
    return (e2 - e2a).subs({"x": vars[0], "y": vars[1]})
    '''return (A*vars[0]**2 + 2*vars[1]**2 - 1)'''

def phi1(vars: list) -> float:
    return e1.subs({"x": vars[0], "y": vars[1]})
    '''return sp.tan(vars[0]*vars[1] + M)'''

def phi2(vars: list) -> float:
    return e2.subs({"x": vars[0], "y": vars[1]})
    '''return sp.sqrt((1 - M*vars[0]**2)/2)'''