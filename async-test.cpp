//=============================================================================
// async tests
// compile command: g++ -std=c++11 -o async-test async-test.cpp  
//=============================================================================

#include <iostream>
#include <array>
#include <thread>
#include <future>

const int tasks = 1000;
std::thread::id last = std::this_thread::get_id();;
int threads = 0;

int f()
{
	std::thread::id t = std::this_thread::get_id();
	if ( t != last ) ++threads;

	int i;
	for (i=0; i<10000; i++);
	return i;
}

int main()
{
	std::array< std::future<int>, tasks > futures;
	for (int i=0; i<tasks; i++)
		futures[i] = std::async(std::launch::async, f);
	
	int total = 0;
	for (int i=0; i<tasks; i++)
		total += futures[i].get();
	std::cout << "Total: " << total << std::endl;
	std::cout << "Threads: " << threads << std::endl;
	return 0;
}
