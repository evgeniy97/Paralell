#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>
#include <thread>
#include <chrono>

// xcrun clang++ -std=c++11 -stdlib=libc++ -Weverything 3-11.cpp

const long N = 10000000;

void merge_sort(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
    if (last - first > 1)
    {
        auto middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}

int main(int arc, char *argv[])
{
    int numt = atoi(argv[1]);

    std::vector<int> v(N);
    std::vector<std::thread> threads;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, 9);

    std::generate(v.begin(), v.end(), std::bind(dis, std::ref(mt)));

    int step = N / numt;
    auto it = v.begin();
    for (int i = 0; i < numt; i++)
    {
        threads.push_back(
            std::thread(merge_sort, it + i * step, it + (i + 1) * step));
    }

    for (int i = 0; i < numt; i++)
    {
        // Подождать каждый поток
        threads[i].join();
    }

    for (int i = 1; i < numt; i++)
    {
        //std::merge(result.begin(), result.end(), v[i].begin(), v[i].end(), std::back_inserter(result));
        std::inplace_merge(it + (i - 1) * step, it + i * step, it + (i + 1) * step);
    };
    /*
    for (auto n : v)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    */
}