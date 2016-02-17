#pragma once

#include "serialize.h"

template <typename R, typename... Args>
struct dispatcher {

	dispatcher(R (*f)(Args...)) : func(f) {}
	
	dispatcher(std::tuple<Args...> params, R (*f)(Args...))
		: args(params), func(f)
		{}

	// recursivelly extract args (from tuple) and pack parameters
	template <typename ...Actual>
	typename std::enable_if<sizeof...(Actual) != sizeof...(Args)>::type
	dispatch(Actual&& ...a) {
    	dispatch(std::forward<Actual>(a)..., std::get<sizeof...(Actual)>(args));
	}

	// called at end of recursion
	void dispatch(Args ...args) {
		result_value = func(args...);
	}

	R call() { dispatch(); return result_value; }	

	void read_args() {
		args = deserialize_args<Args...>();
	}

	// data members
	std::tuple<Args...> args;
	R (*func)(Args...);
	R result_value;

};

