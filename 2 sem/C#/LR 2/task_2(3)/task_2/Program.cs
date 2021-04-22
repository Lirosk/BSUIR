using System;

namespace task_2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!\n\n\nEnter a:");
            int a = Int32.Parse(Console.ReadLine());
            Console.WriteLine("\n\nEnter b:");
            int b = Int32.Parse(Console.ReadLine());

            a = Math.Abs(a);
            b = Math.Abs(b);

            long num = 1;

            for (int i = a; i <=b; i++)
            {
                num *= i;
            }

            int exp = 0;

            for (; (num%(long)Math.Pow(2, exp)) == 0; exp++) { }
            exp -= 1;

            Console.WriteLine("Max exponent of 2 = " + exp);

        }
    }
}
