#pragma once

#include <conio.h>
#include <iomanip.h>
#include <iostream.h>

template <class T>
class Vector
{
protected:
	T* p_vector;
	int size;
	int start_index;
public:
	Vector(int s = 10, int si = 0);//конструктор
	Vector(const Vector& v);//конструктор копирования

};



template <class T>
Vector<T>::Vector(int s,int si)
{
	p_vector = new T[s];
	int size = s;
	int start_index = si;
}