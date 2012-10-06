/*
 * conteneur.cpp
 *
 *  Created on: 6 juin 2011
 *      Author: ANTOINE Sylvestre
 */

#include "conteneur.hpp"

namespace ami
{

std::ostream & operator << (std::ostream & os, const GridLocation & loc)
{
	return os << '[' << loc.first << ',' << loc.second << ']';
}

} // namespace ami
