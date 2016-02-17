//===============================================================
// file: serialize.h
// description: simple data serializing and support for RPC
// author: Marcelo Arroyo (marroyo@dc.exa.unrc.edu.ar)
// licence: GPLv3 (see licence.txt)
// changes:
//   - Oct 24: Initial write
//===============================================================

#pragma once

#include <typeinfo>
#include <typeindex>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

template<typename T>
inline size_t hash_code() { return typeid(T).hash_code(); }

// value serialization
template<typename T>
void serialize(std::ostream & out, T& value)
{
	out << 'v' << hash_code<T>() << ':' << value << ':';
}

// vector serialization
template<typename T>
void serialize(std::ostream & out, std::vector<T>& value)
{
	out << 'A' << hash_code<T>() << ':' 
	    << value.size() << ':';
	for (T elem : value)
		out << serialize(out,elem);
}

// call arguments serialization
void serialize_args(std::ostream & out)
{
}

template<typename T, typename... Args>
void serialize_args(std::ostream & out, T& arg, Args... others)
{
	serialize(out,arg);
	serialize_args(out, others...);
}

// function call serialization
template<typename F, typename... Args>
void serialize_call(std::ostream & out, F & f, Args... args)
{
	out << 'F' << hash_code<F>() << ':' << sizeof...(args) 
	    << ':';
	serialize_args(out, args...);
}

// result serialization
template<typename T>
void serialize_result(std::ostream & out, T & value)
{
	out << 'R';
	serialize(out, value);
}

template<typename T>
void serialize_result(std::ostream & out, T && value)
{
	out << 'R';
	serialize(out, value);
}

//=============================================================================
// Deserealization
//=============================================================================

template<typename T>
std::tuple<T> deserialize_args() {
	return std::tuple<T>(T(1.5f));
}

template<typename T, typename... Others>
typename std::enable_if< sizeof...(Others), std::tuple<T,Others...> >::type
deserialize_args() {
	return std::tuple_cat( std::make_tuple(T(2)), deserialize_args<Others...>() );
}

