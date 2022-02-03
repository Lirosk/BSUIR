using System;
using System.Text;

namespace task_1
{
    class Program
    {
        /*
        В заданной строке поменять порядок слов на обратный (слова разделены пробелами).
        */
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!\n\nEnter the string:\n");

            //string str = Console.ReadLine();
            StringBuilder str = new StringBuilder(Console.ReadLine());
            StringBuilder newStr = new StringBuilder("");
                        
            char temp = '\0';

            int len = str.Length, last = len - 1;
            for (int i = len - 1; i > -1; i--)
            {
                temp = str[i];
                if ((str[i] == ' ') || (i == 0))
                {
                    string tempStr = (str.ToString().Substring(i, last - i + 1));
                    if (i == 0)
                    {
                        newStr.Append(' ');
                    }

                    last -= last - i + 1;
                    newStr.Append(tempStr);
                }
            }
            //str = str.Remove(0, len+1);
            newStr.Remove(0, 1);
            
            Console.WriteLine("\n\nResult:\n"+newStr);
        }
    }
}
