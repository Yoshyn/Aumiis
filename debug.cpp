/*
 * debug.cpp
 *
 *  Created on: 16 juin 2011
 *      Author: sye
 */

#include "debug.hpp"

namespace ami
{

ShowFuncScope::ShowFuncScope (const std::string & func,
							  const std::string & file, const int & line) :
	m_func(func), m_beginPeriod(clock())
{

	std::cout << space << "<" << func << "> [File = " << file << " , Line = "
			<< line << "]" << std::endl << std::flush;
	space += "   ";
}

ShowFuncScope::~ShowFuncScope ()
{
	space.resize(space.length() - 3);
	std::cout << space << "</" << m_func << "> [Time = "
			<< difftime(clock(),m_beginPeriod) << " ms]" << std::endl
			<< std::flush;
}

std::string ShowFuncScope::space;

} // namespace ami
