class Polynomial:
    def __init__(self, coefficient = []):
        self.__coefficient = coefficient.copy()
        if (self.__coefficient[-1] == 0):
            self.__calculate_degree()


    def __getitem__(self, key: int) -> (int, float):
        if not isinstance(key, int):
            raise TypeError(f"indices must be integers, not {type(key).__name__}")
        return self.__coefficient[key]


    def __setitem__(self, key: int, value: (float, int)) -> int:
        self.set_coefficient(key, value)


    def __calculate_degree(self) -> None:
        while (self.__coefficient):
            if not (self.__coefficient[-1] == 0):
                break
            self.__coefficient.pop()

    @property
    def degree(self) -> int:
        if not (self.__coefficient):
            return 0
        return len(self.__coefficient) - 1

    @property
    def coefficients(self) -> list:
        return self.__coefficient.copy()

    def set_coefficient(self, degree: int, value: (int, float)) -> None:
        if not isinstance(degree, int):
            raise TypeError(f"degree of coefficient must be integers, not {type(degree).__name__}")
        
        if not isinstance(degree, (int, float)):
            raise TypeError(f"value type must be int or float, not {type(value).__name__}")
        
        if (degree >= self.degree):
            self.__coefficient += [0]*int(degree - self.degree + 1)

        self.__coefficient[degree] = value
        self.__calculate_degree()


    def diff(self):
        new_coefs = self.__coefficient.copy()[1:]
        for i in range(1, len(new_coefs)):
            new_coefs[i] *= i + 1

        return Polynomial(new_coefs)


    def subs(self, x: float) -> float:
        if not (isinstance(x, (float, int))):
            raise TypeError(f"x must be float, not {type(x).__name__}")

        answer: float = 0

        for i in range(len(self.__coefficient)):
            answer += self.__coefficient[i]*x**i
        
        return answer
