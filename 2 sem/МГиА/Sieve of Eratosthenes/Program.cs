using System;
using System.Collections.Generic;

namespace Sieve_of_Eratosthenes
{
	class Program
	{
		static void Main()
		{
			uint n = 0;

			Console.WriteLine("\nEnter num of int:");
			while (!UInt32.TryParse(Console.ReadLine(), out n))
			{
				Console.WriteLine("Invalid input. Try again:\n");
			}

			if (n == 0)
			{
				return;
			}

			List<uint> primes = new List<uint>();

			if (2 <= n)
			{
				primes.Add(2);
			}

			{
				uint m = 0;
				bool prime = true;

				for (uint i = 3; i <= n; i += 2)
				{
					prime = true;

					m = (uint)Math.Sqrt(i);

					foreach (var j in primes)
					{
						if (j > m)
						{
							break;
						}
						if ((i % j == 0))
						{
							prime = false;
							break;
						}
					}

					if (prime)
					{
						primes.Add(i);
					}
				}
			}

			Console.WriteLine("prime number <= n:\n");
			foreach (var i in primes)
			{
				Console.Write(i + "  ");
			}

			Console.WriteLine();
		}
	}
}
