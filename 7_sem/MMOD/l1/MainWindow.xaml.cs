using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Windows;

namespace l1
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			CultureInfo.CurrentCulture = CultureInfo.GetCultureInfo("en-GB");
			InitializeComponent();
		}

		private static bool TryParse(string text, out double outRes)
		{
			var ret = double.TryParse(text, out var res) && (res >= 0 && res <= 1);
			outRes = res;

			return ret;
		}

		private static double Parse(string text)
		{
			var ret = double.Parse(text);

			if (ret < 0 || ret > 1)
			{
				throw new FormatException();
			}

			return ret;
		}

		private void btnDoIt_Click(object sender, RoutedEventArgs e)
		{
			if (!TryParse(txtP.Text, out var p))
			{
				lblMessage.Visibility = Visibility.Visible;
				return;
			}

			lblMessage.Visibility = Visibility.Hidden;

			var (Total, NumTrue) = Generator.Task1(p);
			var percTrue = 100d * NumTrue / (double)Total;

			spResults.Visibility = Visibility.Visible;

			lblNumTrue.Content = NumTrue;
			lblNumTotal.Content = Total;
			lblPercTrue.Content = percTrue;
		}

		private void t2_btnDoIt_Click(object sender, RoutedEventArgs e)
		{
			double[] ps;

			try
			{
				ps = Array.ConvertAll(t2_txtPs.Text.Split(','), Parse);
			}
			catch (FormatException)
			{
				t2_lblMessage.Visibility = Visibility.Visible;
				return;
			}

			t2_lblMessage.Visibility = Visibility.Hidden;
			t2_lblResDescr.Visibility = Visibility.Visible;

			var (res, total) = Generator.Task2(ps);

			t2_lblRes.Content = string.Join(", ", res.Select(x => 100d * x / (double)total));
			t2_lblTotal.Content = $"Total for each: {total}";
		}

		private void t3_btnDoIt_Click(object sender, RoutedEventArgs e)
		{
			bool successP1 = TryParse(t3_txtP1.Text, out var pa);
			bool successP2 = TryParse(t3_txtP2.Text, out var cpba);

			if (!successP1)
			{
				t3_lblP1Message.Visibility = Visibility.Visible;
			}
			if (!successP2)
			{
				t3_lblP2Message.Visibility = Visibility.Visible;
			}

			if (!successP1 || !successP2)
			{
				return;
			}

			t3_lblP1Message.Visibility = Visibility.Hidden;
			t3_lblP2Message.Visibility = Visibility.Hidden;
			t3_spRes.Visibility = Visibility.Visible;

			var ((AB, AnB, nAB, nAnB), Total) = Generator.Task3(pa, cpba);

			var percAB = 100d * AB / (double)Total;
			var percAnB = 100d * AnB / (double)Total;
			var percnAB = 100d * nAB / (double)Total;
			var percnAnB = 100d * nAnB / (double)Total;

			t3_lblAB.Content = percAB;
			t3_lblAnB.Content = percAnB;
			t3_lblnAB.Content = percnAB;
			t3_lblnAnB.Content = percnAnB;

			t3_lblTotal.Content = Total;
		}

		private void t4_btnDoIt_Click(object sender, RoutedEventArgs e)
		{
			double[] ps;

			try
			{
				ps = Array.ConvertAll(t4_txtPs.Text.Split(","), Parse);
			}
			catch (FormatException)
			{
				t4_lblMessage.Visibility = Visibility.Visible;
				return;
			}

			int[] numHappened;
			int Total;
			try
			{
				if (ps.Aggregate((a, b) => a + b) != 1)
				{
					throw new ArgumentException("Sum of possibilites must be equal to 1");
				}
				(numHappened, Total) = Generator.Task4(ps);
			}
			catch (ArgumentException)
			{
				t4_lblMessage.Visibility = Visibility.Visible;
				return;
			}

			var res = new double[numHappened.Length];

			for (int i = 0; i < res.Length; i++)
			{
				res[i] = 100d * numHappened[i] / (double)Total;
			}

			t4_lblMessage.Visibility = Visibility.Hidden;
			t4_txtPs.Visibility = Visibility.Visible;
			t4_spRes.Visibility = Visibility.Visible;

			t4_lblRes.Content = string.Join(", ", res);
		}

		private class Game
		{
			public string Name { get; set; }
			public double Money { get; set; }

			public Game(string name, double money)
			{
				Name = name;
				Money = money;
			}
		}

		private readonly List<Game> Fortune = new();
		private double TotalMoney = 0;
		private void add_btnAddGame_Click(object sender, RoutedEventArgs e)
		{
			if (!double.TryParse(add_txtMoney.Text, out double money))
			{
				add_lblMessage.Visibility = Visibility.Visible;
				return;
			}

			add_spResGame.Visibility = Visibility.Hidden;

			TotalMoney += money;
			add_lblTotalMoney.Content = TotalMoney;

			add_lblMessage.Visibility = Visibility.Hidden;

			var game = add_txtGame.Text;

			add_txtGame.Text = "";
			add_txtMoney.Text = "";

			int index = -1;
			for (int i = 0; i < Fortune.Count; i++)
			{
				if (Fortune[i].Name == game)
				{
					index = i;
					break;
				}
			}

			if (index == -1)
			{
				Fortune.Add(new(game, money));
				add_lstGames.Items.Add(game);
				add_lstMoney.Items.Add(money);
			}
			else
			{
				Fortune[index].Money += money;
			}

			ReCalcMoney();

		}

		private void ReCalcMoney()
		{
			add_lstPercent.Items.Clear();
			add_lstMoney.Items.Clear();

			foreach (var game in Fortune)
			{
				add_lstPercent.Items.Add(100d * game.Money / TotalMoney);
				add_lstMoney.Items.Add(game.Money);
			}
		}

		private void add_btnClear_Click(object sender, RoutedEventArgs e)
		{
			Fortune.Clear();
			TotalMoney = 0d;

			add_lblTotalMoney.Content = 0;

			add_lstGames.Items.Clear();
			add_lstMoney.Items.Clear();
			add_lstPercent.Items.Clear();
			//add_lstRes.Items.Clear();
		}

		private void add_btnCalc_Click(object sender, RoutedEventArgs e)
		{
			var res = Generator.Happen4(Fortune.Select((game) => game.Money / TotalMoney).ToArray());

			//add_lstRes.Items.Clear();
			//foreach (var num in res)
			//{
			//	add_lstRes.Items.Add(100d * num / (double)total);
			//}

			add_spResGame.Visibility = Visibility.Visible;
			add_lblGameSelected.Content = Fortune[res].Name;
		}
	}
}
