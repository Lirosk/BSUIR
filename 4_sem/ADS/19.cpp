#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int inv = 0;

void merge_sort(int* v, int start, int finish)
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
	int* nums = new int[n];
    
	for (int i = 0; i < n; i++)
	{
		cin >> nums[i];
	}
	
	merge_sort(nums, 0, n-1);

	cout << inv;
}
	