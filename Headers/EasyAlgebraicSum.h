#pragma once
#include <iostream>
#include <math.h>
using namespace std;

float AlgebraicSum() 
{
	int N;
	cout << "Enter quantity of X: ";
	cin >> N;
	float Y = 0.f;
	float* X = (float*)malloc(N * sizeof(float));
	float* Z = (float*)malloc(N * sizeof(float));
	float* B = (float*)malloc(N * sizeof(float));
	float* A = (float*)malloc(N * sizeof(float));
	float* Betta = (float*)malloc(N * sizeof(float));
	int size =  (sizeof(X) + sizeof(Z) + sizeof(B)
		+ sizeof(A) + sizeof(Betta))*N;
	cout <<"Usage of memory: "<<size<<" bytes"<<endl;
	
	for (int i = 0; i < N; i++)
	{
		cout << "X" << i << endl;
		cout << "Enter number Z" << i << endl;
			cin >> Z[i];
		cout << "Enter number B" << i<< endl;
		cin >> B[i];
		cout << "Enter number A" << i << endl;
		cin >> A[i];
		cout << "Enter Betta"    << i<< endl;
		cin >> Betta[i];
		X[i] = (Z[i] * Z[i] * Z[i] - B[i] + 
		(A[i] * A[i]) / tan(Betta[i])* tan(Betta[i]));
		Y += X[i];
	};


	return Y;
}