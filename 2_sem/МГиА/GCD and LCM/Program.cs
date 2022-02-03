using System;

namespace GCD_and_LCM
{
    class Program
    {     
        static void Main()
        {
            int a = 0, b = 0;

            Console.WriteLine("Enter 1st num of int:");
            while (!int.TryParse(Console.ReadLine(), out a))
            {
                Console.WriteLine("Invalid input. Try again:\n");
            }

            Console.WriteLine("Enter 2nd num of int:");
            while (!int.TryParse(Console.ReadLine(), out b))
            {
                Console.WriteLine("Invalid input. Try again:\n");
            }

            Console.WriteLine("\n\npress any key...");
            Console.ReadKey();

            Console.Clear();
            Console.WriteLine($"GCD of {a} and {b} = {GCD(a,b)}\nLCM of {a} and {b} = {LCM(a ,b)}");
        }

        static private int GCD(int a, int b)
        {
            if (a*b == 0)
            {
                return 1;
            }

            if (a < 0)
            {
                a = -a;
            }
            if (b < 0)
            {
                b = -b;
            }

            for (int i = a; i > 0; i--)
            {
                if (a % i == 0 && b % i == 0)
                {
                    return i;
                }
            }

            return 1;
        }

        static private int LCM(int a, int b)
        {
            int hcf, temp, lcm;

            if (a < 0)
            {
                a = -a;
            }
            if (b < 0)
            {
                b = -b;
            }

            hcf = a;
            temp = b;

            while (hcf != temp)
            {
                if (hcf > temp)
                {
                    hcf -= temp;
                }
                else
                {
                    temp -= hcf;
                }
            }

            lcm = (a * b) / hcf;

            return lcm;
        }
    }
}
