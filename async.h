//=============================================================================
// C++11 Parallel and Distributed Programming Templates (pdpt)
// file: async.h
// description: asynchronous call on a given thread pool
// author: Marcelo Arroyo (marroyo@dc.exa.unrc.edu.ar)
// Licence: GPL v3 (see licence.txt)
// Changes:
//   - Oct 22: Initial definition
//=============================================================================

#ifndef PDPT_ASYNC_H
#define PDPT_ASYNC_H

#include "thread_pool.h"

namespace pdpt {

template<class F, class... Args>
auto async(thread_pool& p, F&& f, Args&&... args) 
-> std::future<typename std::result_of<F(Args...)>::type>
{
	return p.enqueue(f,args...);
}

} // end namespace pdpt

#endif

