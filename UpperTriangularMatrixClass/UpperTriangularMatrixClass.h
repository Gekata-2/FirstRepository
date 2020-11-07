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
	Vector(int s = 10, int si = 0);//�����������
	Vector(const Vector& v);//����������� �����������
	~Vector();//����������
	int get_size()//��������� ������� ������
	{
		return size;
	}
	int get_start_index()//��������� ������� ������� ��������
	{
		return start_index;
	}
	T& get_value(int position);//������ � ��������� �������
	T& operator[](int position);
	Vector& operator=(const Vector& vector);
	Vector operator+(const T& value);//��������� ������(�����)

	Vector operator+(const Vector& vector);//�������� 2-� ��������
	Vector operator-(const Vector& vector);//��������� 2-� ��������
	Vector operator*(const Vector& vector);//��������� 2-� ��������
};


//�����������
template <class T>
Vector<T>::Vector(int s, int si)
{
	p_vector = new T[s];
	int size = s;
	int start_index = si;
}

//����������� �����������
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

//������ ��� �������� �������
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


//��������
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

//���������
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