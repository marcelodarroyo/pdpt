#include <iostream>
#include <vector>
#include <chrono>

#include "pdpt.h"

int f(int a, int b)
{
    return a+b;
}

using namespace pdpt;

int main()
{
    
    thread_pool pool(4);
    std::vector< std::future<int> > results;
    int x=1,y=2;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back( pool.enqueue(f,x,y) );
		++x; ++y;
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
   
	// async test
	std::cout << "async test..." << std::endl;
	results.clear();
	for(int i = 0; i < 8; ++i) 
		results.emplace_back( 
			async(pool,
					[i] {
						std::cout << "hello " << i << std::endl;
						std::this_thread::sleep_for(std::chrono::seconds(1));
						std::cout << "world " << i << std::endl;
						return i*i;
					})
		);

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

	// global clock test (5 synchronized updates in each task)
	std::cout << "global clock test..." << std::endl;
	results.clear();
	gclock c(4);
	for (int i=0; i<4; i++)
		results.emplace_back(
			async(	
				pool, 
				[i,&c] 
				{ 
					for (; c<5; c++)
						std::cout << "sync:" << i << ',' << c << std::endl;
					return i;
				}
			)
		);

	for(auto && result: results)
		result.get();

    return 0;
}
