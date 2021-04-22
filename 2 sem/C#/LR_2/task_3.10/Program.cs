using System;
using System.Text;

namespace task_3._10
{
    class Program
    {
        static double Input()
        {
            Console.WriteLine("\n\nEnter your float number:");
            StringBuilder str = new StringBuilder(Console.ReadLine());

            double num = 0;
            
            int numOfPoints = 0, pointLocation = 0;
            bool minus = false;

            if (str[0] == '-')
            {
                str.Remove(0,1);
                minus = true;
            }

            pointLocation = str.Length;

            for (int i = 0; i < str.Length; i++)
            {
                if ((str[i] == '.') || (str[i] == ','))
                {
                    numOfPoints += 1;
                    pointLocation = i;
                }
                else if ((str[i] < '0') || (str[i] > '9'))
                {
                    Console.WriteLine("\n\nIncorrect input.\n");
                    return 0;
                }
            }

            if (numOfPoints > 1)
            {
                Console.WriteLine("\n\nIncorrect input.\n");
                return 0;   
            }

            num = 0;
            for (int i = 0; i < pointLocation; i++)
            {
                num += (str[i] - '0') * Math.Pow(10, pointLocation - i - 1);
            }

            for (int i = pointLocation + 1; i < str.Length; i++)
            {
                num += (str[i] - '0') / Math.Pow(10, i - pointLocation);
            }

            if (minus)
            {
                num *= -1;
            }

            return num;
        }
        
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            double num = 0;

            num = Input();
            
            Console.WriteLine("\n\nYour num: "+num);
        }
    }
}