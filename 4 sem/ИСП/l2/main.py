import jsons
from class_to_check import Ctc
import utility

def main():
    d = jsons.dumps(Ctc, indent=4)
    print(d)
    p = jsons.loads(d)
    print(p.l(10))
    

a = {1: 2, 2: 3}

f = (lambda x :((l := lambda y: (l(y-1) + l(y-2)) if y > 2 else (1 if y == 2 else 0))(x)))
#l = lambda x: x + 2

class V:
    def a():
        print()

def h():
    print("hi")

def F(n):
    if (n == 1):
        return 0
    if (n == 2):
        return 1
    return F(n-1) + F(n-2)
















































if __name__ == "__main__":
    main()