#pragma once
#include <cstdlib>
#include <ctime>


template <class T>
class Matrix {
protected:

public:
    T** arr;
    int height;
    int width;

    
    
    Matrix(int height, int width)
    {
       std::cout << "Вызвался конструктор: " << this << std::endl;
       std::cout << "\n";
        this->height = height;
        this->width = width;
        arr = new T* [this->height];
        for (int i = 0; i < this->height; i++)
            arr[i] = new T[width];

        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                arr[i][j] =/* 0.1**/(rand() % 11-5);
            };
          
        };
        std::cout << std::endl;
    }

        Matrix operator+(const Matrix& SecondMatrix) 
        {
         /* cout << SecondMatrix.arr<<endl;*/
            std::cout << "Вызвалася опреатор сложения матриц: " << this << std::endl;
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
            std::cout << "Вызвалася опреатор присваивания матриц: " << this << std::endl;
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
            std::cout << "Вызвалася опреатор умножения матриц: C " << this << std::endl;

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
            std::cout << "Вызвалась функция printMatrix: " << this << std::endl;
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                    std::cout<<"        "<< arr[i][j] <<"    ";
                std::cout << std::endl;
            }

        }
            /*~Matrix()
            {
                cout << "Вызвался Деструктор" << this<<endl;
                for (int i = 0; i < this->height; i++) 
                {
                    delete[] this->arr[i];
                }
                delete[] this->arr;
            }*/
};



template<class T>
class GaussSolve : public Matrix<T>
{

public:

    GaussSolve(int height, int width) : Matrix<T>(height, width)
    {


    };

    /* void swaplines(float line1[],float line2[],int size)
     {
         int tmpswap;
         for (int i = 0; i < size; i++)
         {
             tmpswap = line1[i];
             line1[i] = line2[i];
             line2[i] = tmpswap;
         };
     }*/
    void printSolve() {
        for (int j = 0; j < this->width; j++)
            std::cout <<"X"<<j+1<< " = " << this->arr[0][j] << "    ";

    }

    void funcGaussSolve(Matrix<T> matrixToSolve)
    {
        T tmpdef = 0;
        T tmpstring = 0;
        //↓Копирование матрицы из принимаемой в Result↓
        GaussSolve Result(matrixToSolve.height, matrixToSolve.width);
        for (int i = 0; i < matrixToSolve.height; i++)
            for (int j = 0; j < matrixToSolve.width; j++)
            {
                Result.arr[i][j] = matrixToSolve.arr[i][j];
            };
        //↑↑↑

        //↓Поиск наибольшей размерности↓
        int tmpsize = 0;
        if (matrixToSolve.height <= matrixToSolve.width)
            tmpsize = matrixToSolve.height;
        else tmpsize = matrixToSolve.width;
        //↑↑↑


        for (int i = 0, j = 0; j < tmpsize; j++, i++)
        {
            if (Result.arr[i][j] != 0)
            {
                //↓Обнуление столбоцов↓
                tmpdef = Result.arr[i][j];

                std::cout << "tmp koeff: " << tmpdef << " i = " << i << " j= " << j << std::endl;

                for (int k = i + 1, n = matrixToSolve.height - j - 1; n > 0; k++, n--)
                {
                    tmpstring = (-1) * Result.arr[k][j] / tmpdef;
                    std::cout << "tmpstring koeff: " << tmpstring << " k = " << k << std::endl;
                    for (int l = 0; l < matrixToSolve.width; l++)
                    {
                        Result.arr[k][l] = Result.arr[k][l] + Result.arr[i][l] * tmpstring;
                        std::cout << Result.arr[k][l] << "         ";
                    };
                    std::cout << std::endl;
                };
                Result.printMatrix();
                //↑↑↑
            }
            else
            {
                //↓Смена строк если ключевой элемент равен 0↓
                cout << "koeff = 0" << endl;
                for (int i = 0; i < matrixToSolve.height - 1; i++)
                {
                    if (Result.arr[i][j] == 0)
                    {
                        int tmpswapJ;
                        for (int j = 0; j < matrixToSolve.width; j++)
                        {
                            tmpswapJ = Result.arr[i][j];
                            Result.arr[i][j] = Result.arr[i + 1][j];
                            Result.arr[i + 1][j] = tmpswapJ;
                        };
                    };
                    Result.printMatrix();
                }
                i--;
                j--;
                //↑↑↑
            }
        };
        Result.printMatrix();
        //↓Есть ли решения?↓
        for (int i = matrixToSolve.height - 1; i >= 0;)
        {
            if (Result.arr[i][matrixToSolve.width - 1] == 0)
                i--;
            if ((Result.arr[i][matrixToSolve.width - 1] != 0)
                && (Result.arr[i][matrixToSolve.width - 2] == 0))
            {
                cout << "\n!!!Решений нет!!!" << endl;
                break;
            };
            if ((Result.arr[i][matrixToSolve.width - 1] != 0)
                && (Result.arr[i][matrixToSolve.width - 2] != 0))
                break;
        };
        //↑↑↑

        GaussSolve<T> Solve(1, matrixToSolve.height);
        if (matrixToSolve.width == matrixToSolve.height+1)
        {
            T tmpp;
            for (int i = tmpsize - 1, j = tmpsize - 1; i >= 0; i--, j--)
            {
                tmpp = Result.arr[i][j];
                for (int t = 0; t <= tmpsize; t++)
                {
                    if (Result.arr[i][t] != 0)
                    {
                        Result.arr[i][t] = Result.arr[i][t] / tmpp;
                    };
                };

            };
            Result.printMatrix();


            for (int i = tmpsize - 1, j = tmpsize - 1; i >= 0; i--, j--)
            {
                for (int k = 0; k < matrixToSolve.width - 1; k++)
                {
                    if (k != i)
                    {
                      
                        std::cout << "\n" << Result.arr[i][matrixToSolve.width - 1] << " - " << Result.arr[i][k] << endl;
                        Solve.arr[0][j] = Result.arr[i][matrixToSolve.width - 1] - Result.arr[i][k];
                        Result.arr[i][matrixToSolve.width - 1] =
                            Result.arr[i][matrixToSolve.width - 1] - Result.arr[i][k];
                        Result.arr[i][k] = 0;
                        

                    }
                   
                };
               
                for (int t = j - 1; t >= 0; t--)
                {
                    std::cout << "\n" << Result.arr[t][j] << " * " << Solve.arr[0][j] << endl;
                    Result.arr[t][j] = Result.arr[t][j] * Solve.arr[0][j];
                    
                };
                Result.printMatrix();

            };
            Result.printMatrix();
          
            std::cout << "\n Решение: \n" << std::endl;
                Solve.printSolve();

        };
    };


};
