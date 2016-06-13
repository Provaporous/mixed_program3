#ifndef MIXED_H_
#define MIXED_H_
#include <iostream>
using namespace std;
class Mixed
{
	friend ostream& operator<< (ostream& s, Mixed& f);
	friend istream& operator >> (istream& s, Mixed& f);
	friend bool operator<(Mixed a, Mixed b);
	friend bool operator>(Mixed a, Mixed b);
	friend bool operator==(Mixed a, Mixed b);
	friend bool operator<=(Mixed a, Mixed b);
	friend bool operator>=(Mixed a, Mixed b);
	friend bool operator!=(Mixed a, Mixed b);
public:
	Mixed(int i = 0);
	Mixed(int i, int n, int d);
	double Evaluate();
	void Simplify();
	void ToFraction();
	int gcd(int a, int b);
	Mixed operator+(Mixed m);
	Mixed operator-(Mixed m);
	Mixed operator*(Mixed m);
	Mixed operator/(Mixed m);
	Mixed& operator++();	// prefix increment
	Mixed operator++(int);	// postfix increment
	Mixed& operator--();	// prefix decrement
	Mixed operator--(int);	// postfix decrement


private:
	int integer;
	int numerator;
	int denominator;
};

#endif

