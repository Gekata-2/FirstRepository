#pragma once

#include <conio.h>
#include <iostream>


template <class T>
class Vector
{
protected:
	T* p_vector;
	int size;
	int start_index;
public:
	Vector(int s = 10, int si = 0);
	Vector(const Vector& v);

	int get_size()
	{
		return size;
	}

	int get_start_index
	{
	 return start_index;
	}
	T& get_value
	(
		int position;
	)
	T& operator[]
	(
		int position;
	)
	
		int operator==
	(
		const Vector &vector
		)
};



template <class T>
Vector<T>::Vector(int s, int si)
{
	p_vector = new T[s];
	int size = s;
	int start_index = si;
}


template<class T>
Vector<T>::Vector(const Vector<T>& vector)
{
	p_vector = new T[vector.size];
	size = vector.size;
	start_index = vector.start_index;
	for (int i = 0; i < size; i++)
	{
		p_vector[i] = vector.p_vector[i];
	}
}


