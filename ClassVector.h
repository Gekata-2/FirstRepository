#pragma once
using namespace std;
#include <iostream>
class Vector {
public:
    int size;
    int* arr;
    Vector(int size)
    {
        cout <<"Вызвался конструктор: " << this<<endl;
        cout << "\n";
        this->size = size;
        this->arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = i;
            cout << arr[i] << endl;
        };
        cout << "\n";
    }
    Vector(const Vector& otherVector)
    {
        this->size = otherVector.size;
        this->arr = new int[otherVector.size];
        for (int i = 0; i < otherVector.size; i++)
        {
            this->arr[i] = otherVector.arr[i];

        };
    }
    Vector operator+ (const Vector& otherVector)
    {
        Vector res = Vector(this->size);
        for (int i = 0; i < this->size; i++)
        {
            res.arr[i] = this->arr[i] + otherVector.arr[i];
        }
        cout << "\n";
        return res;
    }
    Vector& operator=(const Vector& otherVector)
    {
        
        this->size = otherVector.size;
         delete[] this->arr;
        this->arr = new int[otherVector.size];

        for (int i = 0; i < this->size; i++)
        {
            this->arr[i] = otherVector.arr[i];
        }
        return *this;
    }
    void print()
    {
        cout << "Вызвалась функция print для объекта: " << this<<endl;
        for (int i = 0; i < size; i++)
            std::cout << arr[i] << " ";
        std::cout << "\n";
    }
  
    ~Vector() {
        cout << "Вызвался Деструктор: " << this<<"\n";
        delete[] arr;
    }
};

