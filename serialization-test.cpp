#include "dispatcher.h"
#include <map>
#include <fstream>

double f(int a, float b)
{
	std::cout << "called f(" << a << ',' << b << ')' << std::endl;
	return a + b;
}

double call_to_f() 
{
	std::tuple<int> t1(1);
	auto t2 =std::tuple_cat(t1, std::make_tuple(20.5f));
	dispatcher<double,int,float> caller(t2,f);
	return caller.call();
}

template<typename F>
void deserialize_call(std::istream & in, F & f)
{
	char package_type;
	in >> package_type;
	if ( package_type == 'F' ) {
		size_t hash = hash_code<F>();
		std::cout << "Hash (f): " << hash << std::endl;
		in >> hash;
		std::cout << "received hash: " << hash << std::endl;
	}
}

int main()
{
	serialize_call(std::cout,f,1,3.14f);
	std::cout << std::endl;
	serialize_result(std::cout, f(1,3.14f));
	std::cout << std::endl;

	std::cout << "Testing call_to_f()..." << call_to_f() << std::endl;

	std::cout << "Testing deserialization..." << std::endl;
	std::ofstream os("serial.bin");
	serialize_call(os,f,5,10.5f);
	os.close();
	std::ifstream is("serial.bin");
	deserialize_call(is,f);

	dispatcher<double,int,float> caller(f);
	caller.read_args();
	std::cout << std::get<0>(caller.args) << ' ' << std::get<1>(caller.args) << std::endl;

	return 0;
}
