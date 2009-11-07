/*
 * =====================================================================================
 *
 *       Filename:  UltraMath.h
 *
 *        Version:  1.0
 *        Created:  07.11.2009 12:33:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  ULTRAMATH_H
#define  ULTRAMATH_H

#include <gmpxx.h>

/*
class BigNumber
{
public:
	BigNumber();
	BigNumber(const double &number);
	inline const BigNumber operator * (const BigNumber &other)
	{
		BigNumber num;
		int columns = other.m_digits + other.m_precision + m_digits + m_precision - 1;
		for (int col = columns - 1; col >= 0; --col) {
			for (int row = 0; row < other.m_digits + other.m_precision; ++row) {
				std::cout << col << ":" << row << std::endl;
			}
		}
		return num;
	}
	void print();
private:
	static const int m_maxDigits = 2;
	static const int m_maxPrecision = 4;
	static const int m_base = 10;
	char m_number[m_maxDigits + m_maxPrecision];
	int m_digits;
	int m_precision;
};
*/

typedef mpf_class bignum;
//typedef float bignum;

#endif   /* ----- #ifndef ULTRAMATH_H  ----- */

