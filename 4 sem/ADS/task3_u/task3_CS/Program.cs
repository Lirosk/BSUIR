using System;
using System.Collections.Generic;
using System.Linq;

namespace task3_CS
{
	class Program
	{
		static long res;
		static readonly int m = (int)(1e9 + 7);

		static uint Mod(long num)
		{
			int ret = (int)(num % m);
			if (ret < 0)
			{
				ret += m;
			}
			return (uint)ret;
		}

		static long Mul(List<int> list, short s, short f)
		{
			long ret = 1;
			for (int i = s; i < f; i++)
			{
				ret *= list[i];
			}
			return ret;
		}

		static void Main()
		{
			short n, k;
			List<int> nums = new List<int>();

			{
				var i = Console.ReadLine().Split();
				n = (short)Convert.ToInt32(i[0]);
				k = (short)Convert.ToInt32(i[1]);
			}

			foreach (var i in Console.ReadLine().Split())
			{
				nums.Add(Convert.ToInt32(i));
			}


			nums.Sort();

			if (k == 1)
			{
				Console.WriteLine(Mod(nums[n-1]));
				return;
			}
			else if (k == n)
			{
				res = nums.Aggregate((int a, int b) => a * b);
				Console.WriteLine(Mod(res));
				return;
			}

			res = Mul(nums, (short)(n - k), n);

			short l = 1;
			short r = (short)(n - k + 1);
			long buff;

			while (r != 1)
			{
				buff = Mul(nums, 0, l);
				
				if (r != 0)
				{
					buff *= Mul(nums, r, n);
				}

				if (buff > res)
				{
					res = buff;
				}

				r++;
				l++;
				if (r == n)
				{
					r = 0;
				}
			}

			Console.WriteLine(Mod(res));
		}		
	}
}
