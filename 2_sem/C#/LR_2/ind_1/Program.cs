using System;
using System.Security.Cryptography;

namespace ind_1
{
    class Human
    {
        protected string name = "";
        protected int height = 0;
        protected int mass = 0;
    }
    
    class Sportsmen: Human
    {
        
    }
    
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}