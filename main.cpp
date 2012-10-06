//============================================================================
// Name        : main.cpp
// Author	   : ANTOINE Sylvestre
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <typeinfo>

#include "debug.hpp"
#include "conteneur.hpp"
#include "direction.hpp"
#include "functionnal.hpp"
#include "smartPtr.hpp"
using namespace ami;

void sleep (unsigned int ms)
{
	showScopeFunc();
	int goal = ms + clock();
	while (goal > clock())
		;
}

int main ()
{
	showScopeFunc();
	sleep(100);
	separator("<ami::grid Test>");

	ami::Grid<char> map(3,3,'_');
	debugln(map);

	map[GridLocation(2,0)] = '5';
	debugln(map);

	debugln(map.contains(GridLocation(5,5)));

	debugln(map.toVector());

	separator("</ami::grid Test>");
	std::cout << "!!!EXIT SUCCESS!" << std::endl;
	return 0;
}
