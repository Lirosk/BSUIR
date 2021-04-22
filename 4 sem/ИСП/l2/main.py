from jsonserializer import jsonserializer

def main():
    a = A()
    #print(json.dumps(a.__dict__, default = lambda o: o.__dict__, indent=4), "\n"*3)
    s = jsonserializer.dumps(a, indent=4)
    print(s, "\n"*3)
    res = jsonserializer.loads(s)
    print(res, '\n'*3)
    

def f(  a: int, b: int, 
        /,
        c: float, d: float,
        *, 
        e: str, f:str
        ) -> None:
    print(a, b, c, d, e, f)


class B:
    def __init__(self) -> None:
        self._a = 'a'
        self._b = 'b'

    @staticmethod
    def sm() -> None:
        print('this is B!')

class A:
    a: str = 'a'

    def __init__(self, /, *,_f1 = 1, _f2 = '2') -> None:
        self._f1 = _f1
        self._f2 = _f2
        self._f3 = B()
        self.l = [1, 2, '5', 5, {1: 1}, 9]
        self.f4 = 'y i am here'
        self.f5 = 'f5'

    @classmethod
    def printFs(self) -> None:
        print(self._f1,'\n', self._f2, '\n')

    @classmethod
    def A(self) -> None:
        print('This is A')

    L1 = lambda self, x = '': print(f'this is lambda 1{x}!')
    L2 = lambda: print('this is lambda 2!')

    @staticmethod
    def B() -> None:
        print('From A')

if __name__ == '__main__':
    main()
