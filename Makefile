all: libpdpt.a libpdpt.so thread_pool_test serialization_test

libpdpt.a: thread_pool.h gclock.h gclock.cpp
	g++ -std=c++11 -c gclock.cpp -l pthread
	ar cr libpdpt.a gclock.o

libpdpt.so: thread_pool.h gclock.h gclock.cpp
	g++ -std=c++11 -shared -fPIC -o libpdpt.so gclock.cpp

thread_pool_test: libpdpt.so
	g++ -std=c++11 -o thread_pool_test thread_pool_test.cpp gclock.o -l pthread

serialization_test: serialization-test.cpp serialize.h dispatcher.h
	g++ -std=c++11 -Wfatal-errors -o serialization_test serialization-test.cpp
