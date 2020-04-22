#pragma once
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void EqualNumbers(int* a,int* b,int* c)
{
	cout << "Beginning of the Function" << endl;
	cout << "1st nuber = " << *a << endl;
	cout << "2nd nuber = " << *b << endl;
	cout << "3d nuber = " << *c << endl;

	if (*a == *b || *a == *c || *b == *c)
	{
		cout << "Conditions are met" << endl;
		*a = *a + 5;
		*b = *b + 5;
		*c = *c + 5;
		cout << "1st nuber = " << *a << endl;
		cout << "2nd nuber = " << *b << endl;
		cout << "3d nuber = "  << *c << endl;
	}
	else
	{
		cout << "No equal";
	};
}
