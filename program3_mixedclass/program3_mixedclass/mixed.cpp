#include "mixed.h"
#include <iostream>
#include <iomanip>
using namespace std;


ostream& operator<< (ostream& s, Mixed& f)
{

	if (f.integer == 0 && f.numerator == 0)
	{
		s << 0;
		return s;
	}
	if (f.integer == 0 && f.denominator == 1)
	{
		s << f.numerator;
		return s;
	}
	if (f.numerator == 0)
	{
		s << f.integer;
		return s;
	}
	if (f.integer == 0)
	{
		s << f.numerator << '/' << f.denominator;
		return s;
	}

	s << f.integer << ' ' << f.numerator << '/' << f.denominator;
	return s;
}
istream& operator >> (istream& s, Mixed& f)
{
	char junk;
	int tempi, tempn, tempd;
	cin >> tempi >> tempn >> junk >> tempd;
	if (tempi < 0 && tempn < 0)
	{
		f.integer = 0;
		f.numerator = 0;
		f.denominator = 1;
		return s;
	}
	if (tempi < 0 && tempd < 0)
	{
		f.integer = 0;
		f.numerator = 0;
		f.denominator = 1;
		return s;
	}
	if (tempn<0 && tempd<0)
	{
		f.integer = 0;
		f.numerator = 0;
		f.denominator = 1;
		return s;
	}
	if (tempd == 0)
	{
		f.integer = 0;
		f.numerator = 0;
		f.denominator = 1;
		return s;
	}
	else f.denominator = tempd;
	f.integer = tempi;
	f.numerator = tempn;
	return s;
}
bool operator<(Mixed a, Mixed  b) //passed as copies on purpose
{
	a.ToFraction();
	b.ToFraction();
	int newdenominator = a.denominator*b.denominator;

	a.numerator = a.numerator*(newdenominator / b.denominator);
	b.numerator = (newdenominator / a.denominator)*b.numerator;

	if (a.numerator < b.numerator) return true;
	else return false;
}
bool operator>(Mixed a, Mixed b)
{
	return !(a < b);
}
bool operator==(Mixed a, Mixed b)
{
	a.ToFraction();
	b.ToFraction();
	int newdenominator = a.denominator*b.denominator;

	a.numerator = a.numerator*(newdenominator / b.denominator);
	b.numerator = (newdenominator / a.denominator)*b.numerator;

	if (a.numerator == b.numerator)return true;
	else return false;
}
bool operator<=(Mixed a, Mixed b)
{
	if (a < b || a == b)return true;
	else return false;
}
bool operator>=(Mixed a, Mixed b)
{
	if (a > b || a == b)return true;
	else return false;
}
bool operator!=(Mixed a, Mixed b)
{
	return !(a == b);
}
Mixed::Mixed(int i)
{
	integer = i;
	numerator = 0;
	denominator = 1;
}

Mixed::Mixed(int i, int n, int d)
{
	if (i < 0 && n < 0)
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		return;
	}
	if (i < 0 && d < 0)
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		return;
	}
	if (n<0 && d<0)
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		return;
	}
	if (d == 0)
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		return;
	}
	else denominator = d;
	integer = i;
	numerator = n;

}

double Mixed::Evaluate()
{
	double result;
	if (integer>0) result = (double)integer + ((double)numerator / (double)denominator);
	if (integer<0)  result = (double)integer - ((double)numerator / (double)denominator);
	return result;
}
void Mixed::Simplify()
{
	/*
	ToFraction();
	cout << *this;
	bool ispositive = true;
	if (integer<0||numerator < 0 || denominator < 0)
	{
	ispositive = false;
	if (numerator < 0)numerator *= -1;
	if (denominator < 0)denominator *= -1;
	if (integer < 0) integer *= -1;

	}
	if (ispositive)
	{
	while (numerator > denominator)
	{
	numerator = numerator - denominator;
	integer++;
	}
	}
	if (!ispositive)
	{
	while (numerator > denominator)
	{
	numerator = numerator - denominator;
	integer--;
	}


	}
	*/
	int commondemon = gcd(numerator, denominator);
	if (denominator < 0)
	{
		denominator *= -1;
		numerator *= -1;
	}
	if (commondemon > 0)
	{
		numerator = numerator / commondemon;
		denominator = denominator / commondemon;
	}
	if (commondemon < 0)
	{
		numerator = numerator / (commondemon*-1);
		denominator = denominator / (commondemon*-1);
	}
	if (integer >= 0 && numerator >= 0)
	{
		while (numerator >= denominator)
		{
			numerator = numerator - denominator;
			integer++;
		}
	}
	else
	{

		if (numerator<0)numerator *= -1;

		while (numerator >= denominator)
		{
			numerator = numerator - denominator;
			integer--;
		}
	}


}
int Mixed::gcd(int a, int b)
{
	//source wikipedia
	return b == 0 ? a : gcd(b, a % b);
}
void Mixed::ToFraction()
{
	int newnumerator;
	if (integer<0 || numerator<0)newnumerator = (integer*denominator) - numerator;
	else newnumerator = (integer*denominator) + numerator;
	integer = 0;
	numerator = newnumerator;
	int gcdemon = gcd(numerator, denominator);
	if (gcdemon > 1)
	{
		numerator /= gcdemon;
		denominator /= gcdemon;
	}
	if (gcdemon < 1)
	{
		gcdemon *= -1;
		numerator /= gcdemon;
		denominator /= gcdemon;
	}

}
Mixed Mixed::operator+(Mixed m)
{
	Mixed tempL, tempR, result;
	tempL.integer = integer;
	tempL.numerator = numerator;
	tempL.denominator = denominator;
	tempL.ToFraction();
	tempR.integer = m.integer;
	tempR.numerator = m.numerator;
	tempR.denominator = m.denominator;
	tempR.ToFraction();
	tempL.numerator = tempL.numerator*tempR.denominator;
	tempR.numerator = tempR.numerator*tempL.denominator;
	result.denominator = tempL.denominator*tempR.denominator;
	result.numerator = tempL.numerator + tempR.numerator;
	result.Simplify();
	return result;
}
Mixed Mixed::operator-(Mixed m)
{
	Mixed tempL, tempR, result;
	tempL.integer = integer;
	tempL.numerator = numerator;
	tempL.denominator = denominator;
	tempL.ToFraction();
	tempR.integer = m.integer;
	tempR.numerator = m.numerator;
	tempR.denominator = m.denominator;
	tempR.ToFraction();
	tempL.numerator = tempL.numerator*tempR.denominator;
	tempR.numerator = tempR.numerator*tempL.denominator;
	result.denominator = tempL.denominator*tempR.denominator;
	result.numerator = tempL.numerator - tempR.numerator;
	result.Simplify();
	return result;
}
Mixed Mixed::operator*(Mixed m)
{
	Mixed tempL, tempR, result;
	tempL.integer = integer;
	tempL.numerator = numerator;
	tempL.denominator = denominator;
	tempL.ToFraction();
	tempR.integer = m.integer;
	tempR.numerator = m.numerator;
	tempR.denominator = m.denominator;
	tempR.ToFraction();
	result.numerator = tempL.numerator*tempR.numerator;
	result.denominator = tempL.denominator*tempR.denominator;
	result.integer = 0;
	result.Simplify();
	return result;
}
Mixed Mixed::operator/(Mixed m)
{
	Mixed tempL, tempR, result;
	tempL.integer = integer;
	tempL.numerator = numerator;
	tempL.denominator = denominator;
	tempL.ToFraction();
	tempR.integer = m.integer;
	tempR.numerator = m.numerator;
	tempR.denominator = m.denominator;
	tempR.ToFraction();
	result.numerator = tempL.numerator*tempR.denominator;
	result.denominator = tempL.denominator*tempR.numerator;
	result.integer = 0;
	result.Simplify();
	return result;
}
Mixed& Mixed::operator++()	// pre-fix increment
{
	integer = integer + 1;
	return *this;
}

Mixed Mixed::operator++(int)	// post-fix increment
{
	Mixed temp = *this;
	integer = integer + 1;
	return temp;
}

Mixed& Mixed::operator--()	// pre-fix decrement
{
	integer = integer - 1;
	return *this;
}

Mixed Mixed::operator--(int) // post-fix decrement
{
	Mixed temp = *this;
	integer = integer - 1;
	return temp;
}
