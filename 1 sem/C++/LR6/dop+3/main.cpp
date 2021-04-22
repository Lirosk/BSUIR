#include <iostream>
#include <string>
using namespace std;

unsigned long long f(int n) {
	if (n == 0) return 1;
	return n * f(n - 1);
}

int main() {

	while (1)
	{
		string s; // n!/n1!n2!...
		cout << "\n\nEnter your string: "; cin >> s;
		unsigned long long a = f(s.size());
		int counter;
		while (s.size() > 0) {
			char x = s[0];
			counter = 0;
			for (int i = 0; i < s.size(); i++) {
				if (s[i] == x) {
					s.erase(i, 1);
					counter++;
					i--;
				}
			}
			a /= f(counter);
		}
		cout << "\nNumber of anagramms : " << a << "\n";
	}
	return 0;
}