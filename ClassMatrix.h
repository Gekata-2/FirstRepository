#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
class Matrix {
protected:

public:
    float** arr;
    int height;
    int width;

    
    
    Matrix(int height, int width)
    {
       std::cout << "�������� �����������: " << this << std::endl;
       std::cout << "\n";
        this->height = height;
        this->width = width;
        arr = new float* [this->height];
        for (int i = 0; i < this->height; i++)
            arr[i] = new float[width];

        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                arr[i][j] =/* 0.1**/(rand() % 21-10);
            };
          
        };
        std::cout << std::endl;
    }

        Matrix operator+(const Matrix& SecondMatrix) 
        {
         /* cout << SecondMatrix.arr<<endl;*/
            std::cout << "��������� �������� �������� ������: " << this << std::endl;
            Matrix Result(this->height, this->width);
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    Result.arr[i][j] = this->arr[i][j]+SecondMatrix.arr[i][j];
                    std::cout << Result.arr[i][j] << " ";

                };
                std::cout << std::endl;
            };
            return Result;

        }
         
        Matrix& operator=(const Matrix &SecondMatrix)
            {
            std::cout << "��������� �������� ������������ ������: " << this << std::endl;
                this->height = SecondMatrix.height;
                this->width = SecondMatrix.width;
               
                for (int i = 0; i < this->height; i++)
                    delete[] this->arr[i];
                delete[] this->arr;
              
               this-> arr = new float* [this->height];
                for (int i = 0; i < this->height; i++)
                    this->arr[i] = new float[SecondMatrix.width];

                for (int i = 0; i < this->height; i++)
                {
                    for (int j = 0; j < this->width; j++)
                    {
                        this->arr[i][j] = SecondMatrix.arr[i][j];
                    };
                };
                return *this;
            }
            
        Matrix operator*(const Matrix& SecondMatrix)
        {
            std::cout << "��������� �������� ��������� ������: C " << this << std::endl;

            Matrix Result(this->height, SecondMatrix.width);
          

            for ( int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < SecondMatrix.width; j++)
                {
                    Result.arr[i][j] = 0;
                    for (int k = 0; k < this->width; k++)
                    {
                        Result.arr[i][j] = Result.arr[i][j] + this->arr[i][k] * SecondMatrix.arr[k][j];
                    };
                };
            };
          return Result;
        }
      
        void printMatrix()
        {
            std::cout << "��������� ������� printMatrix: " << this << std::endl;
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                    std::cout<<"        "<< arr[i][j] <<"    ";
                std::cout << std::endl;
            }

        }
            /*~Matrix()
            {
                cout << "�������� ����������" << this<<endl;
                for (int i = 0; i < this->height; i++) 
                {
                    delete[] this->arr[i];
                }
                delete[] this->arr;
            }*/
};




class GaussSolve : public Matrix
{
    
public:
    
  
    GaussSolve(int height, int width) : Matrix(height, width) 
    {

        /*std::cout << "�������� �����������: " << this << std::endl;
        std::cout << "\n";
        this->height = height;
        this->width = width;
        this->arr = new float* [this->height];
        for (int i = 0; i < this->height; i++)
           this->arr[i] = new float[width];

        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
               this->arr[i][j] = 0.1*( rand() % 201 - 100);
            };

        };
        std::cout << std::endl;*/
    };
    float tmpdef = 0;
    float tmpstring = 0;
    void funcGaussSolve(Matrix matrixToSolve)
    {
        GaussSolve Result(matrixToSolve.height, matrixToSolve.width);
        for (int i = 0; i<matrixToSolve.height;i++)
            for (int j = 0; j < matrixToSolve.width; j++)
            {
                Result.arr[i][j] = matrixToSolve.arr[i][j];
            };
        int tmpsize = 0;
        if (matrixToSolve.height <= matrixToSolve.width)
            tmpsize = matrixToSolve.height;
        else tmpsize = matrixToSolve.width;

        for (int j = 0, i = 0;  j < tmpsize ; j++, i++)
        {
            tmpdef = Result.arr[i][j];
            std::cout << "tmp koeff: " << tmpdef <<" i = "<< i <<" j= "<< j << std::endl;

            for (int k = i+1, n= matrixToSolve.height - j-1;n>0; k++,n--)
            {
                tmpstring = (-1) * Result.arr[k][j] / tmpdef;
                std::cout << "tmpstring koeff: " << tmpstring << " k = " << k << std::endl;
                for (int l = 0; l < matrixToSolve.width; l++)
                {
                    Result.arr[k][l] = Result.arr[k][l] + Result.arr[i][l]*tmpstring;
                    std::cout << Result.arr[k][l] << "         " ;
                };
                std::cout << std::endl;
            };
            Result.printMatrix();
        };

    };
}; 