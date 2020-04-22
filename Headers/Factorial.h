#pragma once
#include <iostream>

int factorial(int N)
{
	if (N == 0)
		return 0;
	if (N == 1)
		return 1;
	return N * factorial(N - 1);

}