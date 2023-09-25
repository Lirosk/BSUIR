using System;
using System.Collections.Generic;
using System.Windows;

namespace l1
{
	internal static class Generator
	{
		private static readonly Random r = new Random();
		private const int TotalGenerations = (int)1e6;

		public static (int[] Happened, int TotalForEach) Task4(double[] ps)
		{
			var res = new int[ps.Length];

			for (int i = 0; i < TotalGenerations; i++)
			{
				res[Happen4(ps)]++;
			}

			return (res, TotalGenerations);
		}

		public static ((int AB, int AnB, int nAB, int nAnB) Happened, int Total) Task3(double pa, double cpba)
		{
			var res = new int[4];

			// P(!A) = 1 - P(A)
			var pna = 1 - pa;
			// P(B|!A) = 1 - P(B|A)
			var cpbna = 1 - cpba;

			if (pa == 0)
			{
				// P(A) = 0  =>  P(B) = P(B|!A)
				var pb = cpbna;
				var pnb = 1 - pb;
				var pnab = cpbna;

				var pnanb = pnb * (1 - cpbna / pb);

				_ = MessageBox.Show($"P(A) = {pa} => P(!AB) + P(!A!B) = {pnab} + {pnanb} = {pnab + pnanb}");
			}
			else if (pa == 1)
			{
				// P(A) = 1  =>  P(B) = P(B|A)
				var pb = cpba;
				var pnb = 1 - pb;
				var pab = cpba;

				var panb = pnb * (1 - cpba / pb);
				_ = MessageBox.Show($"P(A) = {pa} => P(AB) + P(A!B) = {pab} + {panb} = {pab + panb}");
			}
			else
			{
				// P(AB) = P(A) * P(B|A)
				var pab = pa * cpba;
				var pnab = pna * cpbna;

				// P(B) = P(AB) + P(A!B)
				var pb = pab + pnab;
				var pbn = 1 - pb;

				Console.WriteLine($"P(B) = {pb}");

				// P(A!B) = ( P(!B)/P(A) )*( 1 - P(AB)/P(B) ) 
				var panb = (pbn) * (1 - pab / pb);
				var pnanb = (pbn) * (1 - pnab / pb);

				_ = MessageBox.Show($"P(AB) + P(A!B) + P(!AB) + P(!A!B) = {pab} + {panb} + {pnab} + {pnanb} = {pab + panb + pnab + pnanb}");


				//double weight = 1;
				//for (int i = 0; i < ps.Length; i++)
				//{
				//	if (Happen1(ps[i] * weight))
				//	{
				//		return i;
				//	}

				//	if (i - 1 >= 0)
				//	{
				//		ps[i] += ps[i - 1];
				//	}

				//	weight = 1d / (1 - ps[i]);
				//}

				//return -1;
			}

			for (int i = 0; i < TotalGenerations; i++)
			{
				res[Happen3(pa, cpba)]++;
			}

			return ((res[0], res[1], res[2], res[3]), TotalGenerations);
		}

		public static (int[] NumHappened, int TotalForEach) Task2(double[] ps)
		{
			var res = new int[ps.Length];

			for (int i = 0; i < TotalGenerations; i++)
			{
				int j = 0;
				foreach (var happened in Happen2(ps))
				{
					if (happened)
					{
						res[j]++;
					}
					j++;
				}
			}

			return (res, TotalGenerations);
		}

		public static (int Total, int NumTrue) Task1(double p)
		{
			int numTrue = 0;

			for (int i = 0; i < TotalGenerations; i++)
			{
				if (Happen1(p))
				{
					numTrue++;
				}
			}

			return (TotalGenerations, numTrue);
		}

		/// <summary>
		/// t4
		/// </summary>
		/// <param name="ps">[P(A1), ..., P(An)]</param>
		/// <returns></returns>
		public static int Happen4(double[] ps)
		{
			double weight = 1;
			double prevPsSum = 0;
			for (int i = 0; i < ps.Length - 1; i++)
			{
				if (Happen1(ps[i] * weight))
				{
					return i;
				}

				prevPsSum += ps[i];
				weight = 1d / (1 - prevPsSum);
			}

			return ps.Length - 1;
		}

		/// <summary>
		/// t3
		/// </summary>
		/// <param name="pa">P(A)</param>
		/// <param name="cpba">P(B|A)</param>
		/// <returns></returns>
		static int Happen3(double pa, double cpba)
		{
			// P(!A) = 1 - P(A)
			var pna = 1 - pa;
			// P(B|!A) = 1 - P(B|A)
			var cpbna = 1 - cpba;

			if (pa == 0)
			{
				// P(A) = 0  =>  P(B) = P(B|!A)
				var pb = cpbna;
				var pnb = 1 - pb;
				var pnab = cpbna;

				var pnanb = pnb * (1 - cpbna / pb);

				Console.WriteLine($"P(A) = {pa} => P(!AB) + P(!A!B) = {pnab} + {pnanb} = {pnab + pnanb}");
				return Happen1(pnab) ? 2 : 3;
			}
			else if (pa == 1)
			{
				// P(A) = 1  =>  P(B) = P(B|A)
				var pb = cpba;
				var pnb = 1 - pb;
				var pab = cpba;

				var panb = pnb * (1 - cpba / pb);
				Console.WriteLine($"P(A) = {pa} => P(AB) + P(A!B) = {pab} + {panb} = {pab + panb}");
				return Happen1(pab) ? 0 : 1;
			}
			else
			{
				// P(AB) = P(A) * P(B|A)
				var pab = pa * cpba;
				var pnab = pna * cpbna;

				// P(B) = P(AB) + P(A!B)
				var pb = pab + pnab;
				var pbn = 1 - pb;

				Console.WriteLine($"P(B) = {pb}");

				// P(A!B) = ( P(!B)/P(A) )*( 1 - P(AB)/P(B) ) 
				var panb = (pbn) * (1 - pab / pb);
				var pnanb = (pbn) * (1 - pnab / pb);

				Console.WriteLine($"P(AB) + P(A!B) + P(!AB) + P(!A!B) = {pab} + {panb} + {pnab} + {pnanb} = {pab + panb + pnab + pnanb}");


				double[] ps = { pab, panb, pnab, pnanb };

				double weight = 1;
				for (int i = 0; i < ps.Length; i++)
				{
					if (Happen1(ps[i] * weight))
					{
						return i;
					}

					if (i - 1 >= 0)
					{
						ps[i] += ps[i - 1];
					}

					weight = 1d / (1 - ps[i]);
				}

				return -1;
			}
		}

		/// <summary>
		/// t2
		/// </summary>
		/// <param name="pas">[P(A1), ..., P(An)]</param>
		/// <returns></returns>
		static IEnumerable<bool> Happen2(double[] pas)
		{
			foreach (var p in pas)
			{
				yield return Happen1(p);
			}
		}

		/// <summary>
		/// t1
		/// </summary>
		/// <param name="pa">P(A)</param>
		/// <returns></returns>
		static bool Happen1(double pa)
		{
			if (pa < 0 || pa > 1)
			{
				//throw new ArgumentException("Possibility must be in range [0, 1]", nameof(pa));
			}

			return r.NextSingle() < pa;
		}
	}
}
