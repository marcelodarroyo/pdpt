#include "gclock.h"

using namespace pdpt;

// global clock increment
void gclock::inc()
{
	std::unique_lock<std::mutex> lock{m};
	if (!--counter) {
		clock_value++;
		cond.notify_all();
		counter = tasks;
	} else 
		cond.wait(lock);
}
