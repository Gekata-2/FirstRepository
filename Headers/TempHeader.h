#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;


int factorial(int a, int tmp)
{
	cout << "tmp:" << tmp << endl;
	cout << "a" << a << endl;

	if (tmp > 2)
	{

		tmp--;
		a = a * tmp;
		if (tmp == 2)
			return a;
		else
			return factorial(a, tmp);
	}
	else if (tmp == 2)
	{
		return 2;
	}
	else
	{
		return 1;
	};
}

