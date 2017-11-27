#include "LongLongInt.h"

longLongInt::longLongInt(string s)
{
	istringstream is(s);
	char num;

	while (is.get(num) && num == '0'){}		// skip the zeros
	do {
		// throw an error if num isn't a number
		if (num<'0' || num>'9') throw IllegalInitialization();
		longInt.insert(0, unsigned(num - '0'));
	} while (is.get(num));
}

longLongInt::longLongInt(const longLongInt& other)
{
	for (int i = 0; i < other.longInt.length();++i)
		longInt.insert(i, other.longInt.visit(i));
}

ostream& operator<<(ostream& os, const longLongInt& obj)
{
	ostringstream oss;

	for (int i = obj.longInt.length() - 1;i >= 0;--i)
		// because class singleLinkList doesn't have iterator
		// I use visit() instead of iterator through it is inefficient
		oss << obj.longInt.visit(i);
	os << oss.str();

	return os;
}

istream& operator >> (istream& is, longLongInt& obj)
{
	obj.longInt.clear();
	char num;
	string str;
	is >> str;		// use string's flow control
	istringstream iss(str);

	while (iss.get(num) && num == '0') {}		// skip the zeros
	do {
		// throw an error if num isn't a number
		if (num<'0' || num>'9') throw IllegalInitialization();
		obj.longInt.insert(0, unsigned(num - '0'));
	} while (iss.get(num));

	return is;
}

longLongInt& longLongInt::operator=(const longLongInt& other)
{
	if (this == &other) return *this;
	longInt.clear();

	for (int i = other.longInt.length() - 1;i >= 0;--i)
		longInt.insert(0, other.longInt.visit(i));

	return *this;
}

longLongInt longLongInt::operator+(const longLongInt& other) const
{
	longLongInt result;
	unsigned remainder, carry = 0;
	int L1 = longInt.length(), L2 = other.longInt.length();
	int i = 0;

	// length of result <= L1 || L2
	for (;i < L1 && i < L2;++i) {
		remainder = longInt.visit(i) + other.longInt.visit(i) + carry;
		carry = remainder / 10;
		result.longInt.insert(i, remainder % 10);
	}
	if (i == L1)	L1 = L2;	// L1 <= L2	
	for (;i < L1;++i) {
		remainder = longInt.visit(i) + carry;
		carry = remainder / 10;
		result.longInt.insert(i, remainder % 10);
	}

	if (carry)		// handle the last carry
		result.longInt.insert(i, carry);

	return result;
}