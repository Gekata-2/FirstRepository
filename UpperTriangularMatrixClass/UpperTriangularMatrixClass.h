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
	Vector(int s = 10, int si = 0);//конструктор
	Vector(const Vector& v);//конструктор копирования
	~Vector();//деструктор
	int get_size()//получение размера вктора
	{
		return size;
	}
	int get_start_index()//получение индекса первого элемента
	{
		return start_index;
	}
	T& get_value(int position);//доступ с контролем индекса
	T& operator[](int position);
	Vector& operator=(const Vector& vector);
	Vector operator+(const T& value);//прибавить скаляр(число)

	Vector operator+(const Vector& vector);//сложение 2-х векторов
	Vector operator-(const Vector& vector);//вычитание 2-х векторов
	Vector operator*(const Vector& vector);//умножение 2-х векторов
};


//Конструктор
template <class T>
Vector<T>::Vector(int s, int si)
{
	p_vector = new T[s];
	int size = s;
	int start_index = si;
}

//Конструктор копирования
template<class T>
Vector<T>::Vector(const Vector<T>& vector)
{
	p_vector = new Vector[vector.size];
	for (int i = 0; i < size; i++)
	{
		p_vector[i] = vector.p_vector[i];
	}
}


template <class T>
Vector<T>::~Vector()
{
	delete[] p_vector;
}

//Доступ без контроля индекса
template <class T>
T& Vector<T>::operator[](int position)
{
	return p_vector[position - start_index];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& vector)
{
	if(this!=&vector)
	{
		if(size!=vector.size)
		{
			delete[] p_vector;
			p_vector = new T[vector.size];
		}

		size = vector.size;
		start_index = vector.start_index;

		for(int i=0;i<size;i++)
		{
			p_vector[i] = vector.p_vector[i];
		}
	}
	return *this;

}


template <class T>
Vector<T> Vector<T>::operator+(const T& value)
{

}


//Сложение
template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& vector)
{
	Vector temp(size, start_index);
	
	for (int i = 0; i < size; i++)
	{
		temp.p_vector[i] = p_vector[i] + vector.p_vector[i];

	}
	return temp;
}

//Вычитание
template <class T>
Vector<T> Vector<T>::operator-(const Vector<T>& vector)
{
	Vector temp(size, start_index);

	for (int i = 0; i < size; i++)
	{
		temp.p_vector[i] = p_vector[i] - vector.p_vector[i];

	}
	return temp;
}

template <class T>
Vector<T> Vector<T>::operator*(const Vector<T>& vector)
{
	Vector temp(size, start_index);

	for (int i = 0; i < size; i++)
	{
		temp.p_vector[i] = p_vector[i] * vector.p_vector[i];

	}
	return temp;
}