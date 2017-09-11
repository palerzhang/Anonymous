#ifndef _ANONYMOUS_STRING_H_
#define _ANONYMOUS_STRING_H_

#include <string>
#include <sstream>

using namespace std;

template <class T>
string AsParse(T in)
{
	stringstream ss;
	ss << in;
	return ss.str();
}

#endif