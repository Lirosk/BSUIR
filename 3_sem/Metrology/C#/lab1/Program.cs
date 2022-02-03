using System;
using System.Linq;
using System.Runtime.Serialization.Formatters;

namespace lab1
{
	class Program
	{
        static void Main(string[] args)
        {
            const int lines = 5;
            const int columns = 7;

            var arr = new int[lines, columns];
            var r = new Random();

            var smin = (sum: int.MaxValue, line: 0);
            var smax = (sum: int.MinValue, line: 0);
            var buf = (sum: 0, line: 0);

            for (int i = 0; i < lines; i++)
            {
                buf.sum = 0;
                buf.line = i;
                for (int j = 0; j < columns; j++)
                {
                    //arr[i, j] = int.Parse(Console.ReadLine());

                    arr[i, j] = r.Next(0, 10);

                    buf.sum += arr[i, j];

                    Console.Write(arr[i, j] + "\t");
                }

                Console.Write("\t" + buf);
                Console.WriteLine();

                if (buf.sum > smax.sum)
                {
                    smax = buf;
                }
                if (buf.sum < smin.sum)
                {
                    smin = buf;
                }
            }

            Console.WriteLine("\nmax value: " + smax  + "\nmin value: " + smin);
        }
	}
}