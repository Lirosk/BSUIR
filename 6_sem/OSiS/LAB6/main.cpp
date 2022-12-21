// To compile:  g++ -pthread -o prog main.cpp
// Increase all element in INT array [1024 * 1024] by 1      [0,0,0,...,0] -> [1,1,1,...,1]


#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <pthread.h>

int mutex_index = 0;
std::atomic_int atomic_index(0);

int* create_byte_arr(const int numTasks)
{
    int* arr = new int[numTasks];
    for (int i = 0; i < numTasks; i++)
    {
        arr[i] = 0;
    }
    return arr;
}

void print_arr(int* arr, const int numTasks)
{
    for (int i = 0; i < numTasks; i++)
    {
        std::cout << arr[i] << '\n';
    }
}

bool check_arr(int* arr, const int numTasks)
{
    bool isValid = true;
    for (int i = 0; i < numTasks; i++)
    {
        if (arr[i] != 1)
        {
            isValid = false;
            break;
        }
    }

    return isValid;
}

std::thread* create_threads(void(*f)(int*, const int), int* arr, const int numTasks, const int numThreads)
{
    std::thread* threads = new std::thread[numThreads];
    for (int i = 0; i < numThreads; i++)
    {
        threads[i] = std::thread((*f), arr, numTasks);
    }

    return threads;
}

void start_threads(std::thread* threads, const int numThreads)
{
    for (int i = 0; i < numThreads; i++)
    {
        threads[i].join();
    }
}

pthread_mutex_t lock;

void increase_arr_mutex(int* arr, const int numTasks)
{
    int i;
    // std::mutex mtx;

    while (true)
    {
        pthread_mutex_lock(&lock);
        // mtx.lock();
        i = mutex_index++;
        // mtx.unlock();
        pthread_mutex_unlock(&lock);

        if (i < numTasks)
        {
            arr[i] += 1;
            // std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }
        else break;
    }
}

void increase_arr_atomic(int* arr, const int numTasks)
{
    int i;
    while (true)
    {
        i = atomic_index++;

        if (i < numTasks)
        {
            arr[i] += 1;
            // std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }
        else break;
    }
}

int main()
{
    const int numTasks = 1024 * 1024;
    const int numThrdSize = 2;
    const int numThreads[numThrdSize]{2, 4};

    int* arr;
    std::thread* threads;

    std::cout << "Mutex:\n";
    for (int i = 0; i < numThrdSize; i++)
    {
        mutex_index = 0;
        arr = create_byte_arr(numTasks);
        threads = create_threads(increase_arr_mutex, arr, numTasks, numThreads[i]);

        auto start = std::chrono::high_resolution_clock::now();
        start_threads(threads, numThreads[i]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "\t" << numThreads[i] << " threads. Duration time: " << duration.count() << "ms\n";
        std::cout << "\t" << "Status: " << (check_arr(arr, numTasks) ? "OK" : "FAILED");
        std::cout << "\n\n";

        delete[] arr;
        delete[] threads;
    }

    std::cout << "\n\n";
    std::cout << "Atomic:\n";
    for (int i = 0; i < numThrdSize; i++)
    {
        atomic_index = 0;
        arr = create_byte_arr(numTasks);
        threads = create_threads(increase_arr_atomic, arr, numTasks, numThreads[i]);

        auto start = std::chrono::high_resolution_clock::now();
        start_threads(threads, numThreads[i]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "\t" << numThreads[i] << " threads. Duration time: " << duration.count() << "ms\n";
        std::cout << "\t" << "Status: " << (check_arr(arr, numTasks) ? "OK" : "FAILED");
        std::cout << "\n\n";

        delete[] arr;
        delete[] threads;
    }

    return 0;
}