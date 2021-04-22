#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

unsigned long long f(int n) {
	if (n == 0) return 1;
	return n * f(n - 1);
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	string s; // n!/n1!n2!...
	cout << "Введите строку : "; cin >> s;
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
	cout << "Количество анаграмм : " << a;
	return 0;
}