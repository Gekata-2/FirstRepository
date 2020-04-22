#pragma once
#include <iostream>
#include <cmath>
using namespace std;

int NdegK(int N, int k)
{
	int tmp=0;
	for (int i = 1; i < N+1; i++)
	{
		tmp = tmp + pow(i, k);
	};

	return tmp;
}