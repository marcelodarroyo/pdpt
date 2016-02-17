//====================================================================================
// file: gclock.h
// description: global logical clock (generational barrier)
// author: Marcelo Arroyo (marroyo@dc.exa.unrc.edu.ar)
//====================================================================================

#ifndef PDPT_LCLOCK_H
#define PDPT_LCLOCK_H

#include <mutex>
#include <condition_variable>

namespace pdpt {

class gclock {
public:
	gclock(std::size_t num_tasks) : 
		tasks(num_tasks), counter(num_tasks), clock_value(0)
	{}

	// copy constructor
	gclock(const gclock& other) : 
		tasks(other.tasks), counter(other.counter), clock_value(other.clock_value)
	{}

	// pre-increment
	gclock& operator++() { inc(); return *this; }
	
	// post-increment
	gclock operator++(int) { inc(); return gclock(*this); }

	// cast to int
	operator int() { return clock_value; }

private:

	void inc();

	std::mutex m;
	std::condition_variable cond;
	const std::size_t tasks;
	std::size_t counter;
	std::size_t clock_value;
};

} // namespace pdpt

#endif
