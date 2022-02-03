using System;
using System.Numerics;

namespace task_2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!\n\n\nEnter a:");
            BigInteger a = BigInteger.Parse(Console.ReadLine());
            Console.WriteLine("\n\nEnter b:");
            BigInteger b = BigInteger.Parse(Console.ReadLine());

            BigInteger num = 1;

            for (BigInteger i = a; i <=b; i++)
            {
                num *= i;
            }
            
            int exp = 0;

            for (; (num % 2) == 0; exp++, num/=2) ;
            exp -= 1;

            Console.WriteLine("Max exponent of 2 is " + exp);
        }
    }
}
