/*
 * direction.cpp
 *
 *  Created on: 6 juin 2011
 *      Author: ANTOINE Sylvestre
 */

#include "direction.hpp"

namespace ami
{

const Direction FourDirectionSet::directions [4] = { UP, LEFT, DOWN, RIGHT };
const Direction FourDirectionSet::opposedDirections [4] = { DOWN, RIGHT, UP,
															LEFT };
const Direction FourDirectionSet::leftDirections [4] =
		{ LEFT, DOWN, RIGHT, UP };
const Direction FourDirectionSet::rightDirections [4] =
		{ RIGHT, UP, LEFT, DOWN };

} // namespace ami
