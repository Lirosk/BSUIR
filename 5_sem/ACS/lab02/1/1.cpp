#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <chrono>
#include <condition_variable>
#include <vector>

using namespace std;

vector<char> give();
void re_arr();
bool arr_is_full_of_ones();
void printarr(int = -1);

void do_it_with_atomic();
void do_it_with_mutex();
void do_it_with_atomic_and_10ns();
void do_it_with_mutex_and_10ns();

int get_index();
int get_index_10ns();
int get_atomic_index();
int get_atomic_index_10ns();

int indx{ 0 };
atomic<int> atomic_indx{ 0 };
vector<char> arr = give();
mutex mtx;
thread threads[32];
int numTasks = 1 << 20;
int NumThreads[]{ 4, 8, 16, 32 };

int main()
{
	void (*funcs[])() = { do_it_with_mutex, do_it_with_mutex_and_10ns, do_it_with_atomic, do_it_with_atomic_and_10ns };
	
	re_arr();

	indx = 0;

	for (auto mutex_or_atomic : { 0, 2 })
	{
		for (auto none_or_10ns_sleep : { 0, 1 })
		{
			cout << "\tmeasuring indexing with ";
			cout << (!mutex_or_atomic ? "mutex" : "atomic");
			if (none_or_10ns_sleep)
			{
				cout << "\n\t";
				cout << "with 10ns sleep";
			}
			cout << "\n\n\n";

			for (int numThreads : NumThreads)
			{
				re_arr();

				indx = 0;
				atomic_indx = 0;

				auto start = chrono::high_resolution_clock::now();

				for (int i = 0; i < numThreads; i++)
				{
					threads[i] = thread(funcs[mutex_or_atomic + none_or_10ns_sleep]);
				}

				for (int i = 0; i < numThreads; i++)
				{
					threads[i].join();
				}

				auto end = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

				cout << "is arr full of ones: " << arr_is_full_of_ones() << "\n";
				int count = duration.count();
				cout << count / 1000 << "," << count % 1000 << " mcs with num of threads: " << numThreads << "\n\n";
			}

			cout << "##########################################\n\n";
		}
	}
}

void re_arr()
{
	for (int i = 0; i < numTasks; i++)
	{
		arr[i] = 0;
	}
}

vector<char> give()
{
	vector<char> res;
	for (int i = 0; i < numTasks; i++)
	{
		res.push_back(0);
	}
	return res;
}

bool arr_is_full_of_ones()
{
	for (int i = 0; i < numTasks; i++)
	{
		if (arr[i] != 1)
		{
			return false;
		}
	}
	return true;
}

void printarr(int len)
{
	if (len < 0)
	{
		len = numTasks;
	}
	for (int i = 0; i < len; i++)
	{
		cout << (int)arr[i] << ' ';
	}
	cout << "\n";
}



int get_index()
{
	lock_guard<mutex> l(mtx);
	return indx++;
}
void do_it_with_mutex()
{
	int i;
	while ((i = get_index()) < numTasks)
	{
		arr.at(i)++;
	}
}



int get_index_10ns()
{
	lock_guard<mutex> l(mtx);
	this_thread::sleep_for(10ns);
	return indx++;
}
void do_it_with_mutex_and_10ns()
{
	int i;
	while ((i = get_index_10ns()) < numTasks)
	{
		arr.at(i)++;
	}
}



int get_atomic_index()
{
	return atomic_indx++;
}
void do_it_with_atomic()
{
	int i;
	while ((i = get_atomic_index()) < numTasks)
	{
		arr.at(i)++;
	}
}



int get_atomic_index_10ns()
{
	this_thread::sleep_for(10ns);
	return atomic_indx++;
}
void do_it_with_atomic_and_10ns()
{
	int i;
	while ((i = get_atomic_index_10ns()) < numTasks)
	{
		arr.at(i)++;
	}
}
