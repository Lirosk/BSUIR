using System;

namespace Diophantine_equation
{
	class Program
	{
		static void Main()
		{
			int a = 0, b = 0, c = 0;

			while (a == 0 && b == 0 && c == 0)
			{
				Console.Clear();

				Console.WriteLine("Equation: ax + by = c\n");

				Console.WriteLine("\nEnter a of int:");
				while (!int.TryParse(Console.ReadLine(), out a))
				{
					Console.WriteLine("Invalid input. Try again:\n");
				}

				Console.WriteLine("\nEnter b of int:");
				while (!int.TryParse(Console.ReadLine(), out b))
				{
					Console.WriteLine("Invalid input. Try again:\n");
				}

				Console.WriteLine("\nEnter c of int:");
				while (!int.TryParse(Console.ReadLine(), out c))
				{
					Console.WriteLine("Invalid input. Try again:\n");
				}
			}

			Console.WriteLine("\n\n");

			if (a == 0 && c / b == 0)
			{
				Console.WriteLine("Equation has no int solutions.\n");
				return;
			}

			if (b == 0 && c / a == 0)
			{
				Console.WriteLine("Equation has no int solutions.\n");
				return;
			}

			if ((double)(c / GCD(a, b)) != ((double)c / GCD(a, b))) //1
			{
				Console.WriteLine("Equation has no int solutions.\n");
				return;
			}

			if (b == 0 && ((double)(c / a) == ((double)c / a))) //2
			{
				Console.WriteLine("Solution : {(" + c / a + ", t) | t of Z}");
				return;
			}

			if (a == 0 && ((double)(c / b) == ((double)c / b))) //3
			{
				Console.WriteLine("Solution : {(t, " + c / b + ") | t of Z}");
				return;
			}

			int d = GCD(a, b);

			int u, v;

			EuclidsAlgorithm(a/d, b/d, out u, out v);

			int x = (u * c) / d, y = (v * c) / d;

			Console.WriteLine("Solution: {(" + x + " " + ((b / d > 0) ? ("+") : ("-")) + " " + Math.Abs(b / d) + "t, "
				+ y + " " + ((a / d > 0) ? ("-") : ("+")) + " " + a / d + "t) | t of Z}");
		}

		static private void EuclidsAlgorithm(int a, int b, out int u, out int v)
		{
			int buf = 0;

			bool minusa = false, minusb = false;

			if (a < 0)
			{
				minusa = true;
				a = -a;
			}
			if (b < 0)
			{
				minusb = true;
				b = -b;
			}

			int k = 0;

			u = 1; v = 0; int ul = 0, vl = 1;

			if (b > a)
			{
				buf = b;
				b = a;
				a = buf;

				u = 0;
				v = 1;
				ul = 1;
				vl = 0;
			}


			while ((double)(a / b) != ((double)a / b))
			{
				k = a / b;

				buf = u;
				u = ul - u * k;
				ul = buf;

				buf = v;
				v = vl - v * k;
				vl = buf;

				buf = b;
				b = a - k * b;
				a = buf;
			}

			if (minusa)
			{
				v *= -1;
			}
			if (minusb)
			{
				u *= -1;
			}

			buf = u;
			u = v;
			v = buf;
		}

		static private int GCD(int a, int b)
		{
			if (a * b == 0)
			{
				return 1;
			}

			if (a < 0)
			{
				a = -a;
			}
			if (b < 0)
			{
				b = -b;
			}

			for (int i = a; i > 0; i--)
			{
				if (a % i == 0 && b % i == 0)
				{
					return i;
				}
			}

			return 1;
		}
	}
}
