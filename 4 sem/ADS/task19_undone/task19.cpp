#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int inv = 0;

void merge_sort(vector<double>& v, int start, int finish)
{
	int m = (finish + start) / 2;

	if ((m + 1 - start) > 1)
	{
		merge_sort(v, start, m);
	}
	if ((finish - m) > 1)
	{
		merge_sort(v, m + 1, finish);
	}
	
	int i = start;
	int j = m + 1;
	vector<int> res;

	while ((i < m + 1) && (j <= finish))
	{
		if (v[j] < v[i])
		{
			res.push_back(v[j]);
			inv += m + 1 - i;
			j += 1;
		}
		else
		{
			res.push_back(v[i]);
			i += 1;
		}
	}
	while (i < m + 1)
	{
		res.push_back(v[i]);
		i += 1;
	}
	while (j <= finish)
	{
		res.push_back(v[j]);
		j += 1;
	}
	for (int _i = 0; _i < finish-start+1; _i++)
	{
		v[start + _i] = res[_i];
	}
	res.clear();
}

int main() 
{
	int n;
	string s;
	cin >> n;
	std::getline(cin >> std::ws, s);
	vector<double> nums(n, 0);

	int i = 0;
	double b = 0;
	bool flt = false;
	double d = 1;
	for (auto c : s)
	{	
		if (c == ' ')
		{	
			nums[i] = b;
			flt = false;
			d = 1;
			b = 0;
			i += 1;
			continue;
		}
		else if (c == '.')
		{
			flt = true;
			continue;
		}
		
		if (!flt)
		{
			b *= 10;
			b += (int)((int)c - '0');
		}
		else
		{
			d /= 10.;
			b += ((int)c - '0')*d;						
		}
	}
	nums[i] = b;
	
	merge_sort(nums, 0, n-1);

	cout << inv;
}
	