_ = "string string";

_ =          5 + 5;

_ = 1 + 2;
_ = 0 -                3;
_ = 9 / 5;
_ = 4 * 3           ;

_ = (1 +2) * 3;
_ = (9 - 4)/7;
_ = 5 + 3 - 2;

float prevar;
int variable = 2;

const int _1 =1; const int _2= 2;const int _3=3;

var a = 3d;
double b = a + 5;
var c=(1.5435e6+b)*0.543f;


(_, _) = (2f, 2d);
(_, _) = (2m, 2u);
(_, _) = (2l, 2L);
(_, _) = (2ul, 2UL);

a += c - b;
b -= (a + c) * 0.11e2D;
c *= a * b;

_ = a < b;
_ = b >= c;

// return a - b + c
int func(int a, int b, int c)
{
    for (int i = 0; i < b; i++)
    {
        a--;
    }

    while (c > 0)
    {
        a ++;
        c--;
    }

    return a;
}

c = func(5, 4, 2);
WriteLine(c);

(a, b) = (1, 2 + c);
WriteLine(a);
WriteLine(b);

WriteLine(a < b);
WriteLine((a + b) * 2);

int e = 10;
WriteLine(1 << e);
