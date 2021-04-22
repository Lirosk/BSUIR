using System;

namespace Division_with_remainder
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

            Console.WriteLine("\nEnter 2nd num of int:");
            while (!int.TryParse(Console.ReadLine(), out b))
            {
                Console.WriteLine("Invalid input. Try again:\n");
            }

            Console.WriteLine("\npress any key...");
            Console.ReadKey();
            Console.Clear();

            Console.Write($"{a} = {a / b}*" + ((b > 0)?($"{b}"):($"({b})")) + ((a % b > 0) ? (" + ") : (" - ")) + $"{Math.Abs(a % b)}\n");
            Console.Write($"\n{b} = {b / a}*" + ((a > 0) ? ($"{a}") : ($"({a})")) + ((b % a > 0) ? (" + ") : (" - ")) + $"{Math.Abs(b % a)}\n");
        }
    }
}
