def main() -> None:
    global K
    N, K = input().split()
    N = int(N)
    K = int(K)

    s = S()

    nums = input().split()
    for i in nums:
        s.push(int(i))

    print(int(s.top()[2] % (10**9 + 7)))


class S:
    def __init__(self) -> None:
        self.s = []
        self.n = 0
        self.lasts = []
        self.zeros = 0


    def push(self, el: int) -> None:
        self.lasts.append(el)
        if not el:
            self.zeros += 1

        if (self.s):
            fmm = 0
            lm = self.s[-1][1]
            mm = self.s[-1][2]
        
            fcm = el
            if lm:
                fcm *= lm

            if self.n == K:
                last = self.lasts.pop(0)

                if self.zeros:
                    if not last:
                        self.zeros -= 1
                    last = 1

                fcm /= last
            
            if not self.zeros:
                fmm = fcm
                if mm is not None:
                    fmm = fmm if fmm > mm else mm
            if self.n != K and self.n != K - 1:
                fmm = None

            self.s.append([el, fcm, fmm])
        else:
            self.s.append([el, el, None])

        if self.n < K:
            self.n += 1
        

    def top(self) -> list:
        return self.s[-1]


if __name__ == "__main__":
    main()