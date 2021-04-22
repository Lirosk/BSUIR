using System;
using System.Collections.Generic;

namespace Canonical_factorization
{
	class Program
	{
		static void Main()
		{
			int num = 0;
			bool minus = false;

			Console.WriteLine("\nEnter num of int:");
			while (!int.TryParse(Console.ReadLine(), out num))
			{
				Console.WriteLine("Invalid input. Try again:\n");
			}

			if (num < 0)
			{
				num = -num;
				minus = true;
			}

			uint n = (uint)num;

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

			Console.Write("\n\n" + num*(minus?(-1):(1)) + " = ");

			if (minus)
			{
				Console.Write("(-1)");
			}

			foreach (var i in primes)
			{
				n = 0;

				while ((double)(num / i) == ((double)num / i))
				{
					num /= (int)i;
					n++;
				}

				if (n != 0)
				{
					if (n == 1)
					{
						Console.Write($"({i})");
					}
					else
					{
						Console.Write($"({i}^{n})");
					}
				}
			}
		}
	}
}
