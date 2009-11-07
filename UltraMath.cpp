/*
 * =====================================================================================
 *
 *       Filename:  UltraMath.cpp
 *
 *
 *        Version:  1.0
 *        Created:  07.11.2009 12:33:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "UltraMath.h"

#include <iostream>

/*

const int BigNumber::m_maxDigits;
const int BigNumber::m_maxPrecision;
const int BigNumber::m_base;

BigNumber::BigNumber()
{
	m_digits = 0;
	m_precision = 0;
	for (int digit = 0; digit < m_maxDigits + m_maxPrecision; ++digit) {
		unsigned char c = 0x00;
		m_number[digit] = c;
	}
}

BigNumber::BigNumber(const double &number)
{
	m_digits = 0;
	m_precision = 0;

	for (int digit = -m_maxDigits + 1; digit <= m_maxPrecision; ++digit) {
		double newNumber;
		if (digit < 0) {
			unsigned long mult = 1;
			for (int i = 0; i > digit; --i) {
				mult *= m_base;
			}
			newNumber = number / double(mult);
		}
		else if (digit > 0) {
			unsigned long mult = 1;
			for (int i = 0; i < digit; ++i) {
				mult *= m_base;
			}
			newNumber = number * double(mult);
		}
		else {
			newNumber = number;
		}
		unsigned char data = int(newNumber) % m_base;
		if (data > 0) {
			if (digit <= 0) {
				if (m_digits == 0) {
					m_digits = -digit + 1;
				}
			}
			else if (digit > 0) {
				m_precision = digit;
			}
		}
		m_number[digit + m_maxDigits - 1] = data;
	}
}

void BigNumber::print()
{
	int start = m_maxDigits - m_digits;
	if (start == m_maxDigits) {
		start--;
	}
	for (int digit = start; digit < m_maxDigits; ++digit) {
		std::cout << char(m_number[digit] + '0');
	}
	if (m_precision == 0) {
		std::cout << std::endl;
		return;
	}
	std::cout << ".";
	for (int digit = m_maxDigits; digit < m_maxDigits + m_precision; ++digit) {
		std::cout << char(m_number[digit] + '0');
	}
	std::cout << std::endl;
}
*/

