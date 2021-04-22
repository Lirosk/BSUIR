#include <iostream>
#include <string>
#include <cmath>


int likefact(int num)
{
	if ((num == 1))
		return 1;
	return num + likefact(num - 1);
}


int main()
{
	for (int kol = 1; kol++;)
	{

		int L, m;
		std::cout << "Enter the length of S string & 'm': ", std::cin >> L >> m;
		//m = (int)pow(10, m);

		std::string S1, S2, Sprov;
		printf("Enter S1 and S2\n");
		std::cin >> (S1) >> (S2);


		int len = (S1.length() < S2.length()) ? (S1.length()) : (S2.length());
		std::string Smal, Sbol;
		if ((S1.length() <= S2.length()))
		{
			Smal = S1;
			Sbol = S2;
		}
		else
		{
			Sbol = S1;
			Smal = S2;
		}
		//std::string Smal = (S1.length() < S2.length()) ? (S1) : (S2);
		//std::string Sbol = (S1.length() > S2.length()) ? (S1) : (S2);
		bool gogo = 1, nal = 0;
		for (int i = 1; (i <= likefact(len)) & (gogo); i++)
		{
			for (int j = 0; (j + i <= len) & (gogo); j++)
			{
				Sprov = Smal.substr(j, i);
				//std::cout << "\n"<< Sprov << "\n";
				if (/*1*/((Smal.find(Sprov) == 0) & (Sbol.find(Sprov) == Sbol.length() - i)) /*1*/ | /*2*/ ((Smal.find(Sprov) == len - i) & (Sbol.find(Sprov) == 0)) /*2*/)
				{
					//std::cout << "\n//\n"<< Smal << "\n" << Sbol << "\n" << Sprov << "\n//\n"<<Smal.find(Sprov)<<"\n"<< Sbol.find(Sprov) <<"\n//\n";
					gogo = 0;
					nal = 1;
				}
			}
		}

		//std::cout<<"\n"<<Sprov<<" : Sprov\n";

		if ((S1.length() + S2.length() - nal * Sprov.length() == L))
		{
			std::cout << "\nCase " << kol - 1 << ":\t1\n\n\n";
		}
		else if ((S1.length() + S2.length() - nal * Sprov.length() > L))
		{
			std::cout << "\nCase " << kol - 1 << ":\t0\n\n\n";
		}
		else
		{
			std::cout << "\nCase " << kol - 1 << ":\t" << ((long long int)pow(26, L - S1.length() - S2.length()) * 2) % m << "\n\n\n";
		}

	}
	return 0;
}
