#ifndef LONGLONGINT_GUARD
#define LONGLONGINT_GUARD
#include "singleLinkList.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class IllegalInitialization{};
class longLongInt;

ostream& operator<< (ostream&, const longLongInt&);
istream& operator>> (istream&, longLongInt&);

class longLongInt
{
	friend ostream& operator << (ostream&, const longLongInt&);
	friend istream& operator >> (istream&, longLongInt&);
public:
	longLongInt(string);
	longLongInt() = default;
	longLongInt(const longLongInt&);
	longLongInt& operator=(const longLongInt&);
	longLongInt operator+(const longLongInt&) const;
	~longLongInt(){}

private:
	singleLinkList<unsigned> longInt;
};

#endif // !LONGLONGINT_GUARD
