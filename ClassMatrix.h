#pragma once
#include <cstdlib>
#include <ctime>

template <class T>
class Matrix {
public:
   
    T** arr;
    int height;
    int width;
    
    Matrix(int height, int width)
    {
       
      
        this->height = height;
        this->width = width;
        arr = new T* [this->height];
        for (int i = 0; i < this->height; i++)
            arr[i] = new T[width];

        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                arr[i][j] =(rand() % 11-5);
            };
          
        };
  
    }
    //Конструктор копирования
    Matrix(const Matrix& CopyMatrix)
    {
        this->height = CopyMatrix.height;
        this->width = CopyMatrix.width;
        this->arr = new T * [this->height];
        for (int i = 0; i < this->height; i++)
            this->arr[i] = new T[width];

        for (int i = 0; i < CopyMatrix.height; i++)
        {
            for (int j = 0; j < CopyMatrix.width; j++)
            {
                this->arr[i][j] = CopyMatrix.arr[i][j];
            };

        };

    }

   
         
        Matrix& operator=(const Matrix &SecondMatrix)
        {
            if (this != &SecondMatrix)
            {
                
                for (int i = 0; i < this->height; i++)
                    delete[] this->arr[i];
                delete[] this->arr;

                this->height = SecondMatrix.height;
                this->width = SecondMatrix.width;

                this->arr = new T* [this->height];
                for (int i = 0; i < this->height; i++)
                    this->arr[i] = new T[SecondMatrix.width];

                for (int i = 0; i < this->height; i++)
                {
                    for (int j = 0; j < this->width; j++)
                    {
                        this->arr[i][j] = SecondMatrix.arr[i][j];
                    };
                };
                return *this;
            }
        }
        Matrix operator+(const Matrix& SecondMatrix)
        {
            try 
            {
                if ((this->width != SecondMatrix.width) || (this->height != SecondMatrix.height))
                {
                    int a = -1;
                    throw a;
                }
                else 
                {
                    Matrix Result(this->height, this->width);
                    for (int i = 0; i < this->height; i++)
                    {
                        for (int j = 0; j < this->width; j++)
                        {
                            Result.arr[i][j] = this->arr[i][j] + SecondMatrix.arr[i][j];
                           

                        };
                        
                    };
                    return Result;
                }
            }
            catch (int)
            {
                std::cout << "\n !!!Ошбика: Матрицы разных размерностей(не подходит для сложения)\n!!!Завершение программы" << std::endl;
                exit(1);
              
            };

        }
        Matrix operator*(const Matrix& SecondMatrix)
        {
            try 
            {
                if(this->width == SecondMatrix.height)
                {
                    Matrix Result(this->height, SecondMatrix.width);

                    for (int i = 0; i < this->height; i++)
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
                else
                {
                    int a = -1;
                    throw a;
                }
            }
            catch (int)
            {
                std::cout << "\n !!!Ошбика:Количество столбцов первой матрицы не равно количеству строк второй матрицы(не подходят под умножение)!!!\nЗавершение программы" << std::endl;
               exit(1);
               
            };
        }
        
        void printMatrix()
        {
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    std::cout.width(3);
                    std::cout << arr[i][j];
                }
                std::cout << std::endl;
            }

        }
        void printExtendedMatrix()
        {
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    if (j == this->width - 1)
                        std::cout << " | ";
                    std::cout.width(7);
                    std::cout<< arr[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

            ~Matrix()
            {
                if (*arr != nullptr)
                {
                    for (int i = 0; i < this->height; i++)
                    {
                        delete[] this->arr[i];
                    }
                    delete[] this->arr;
                }
            }
};


template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& Matrix)
{
    os << "\n";
  
   for (int i = 0; i < Matrix.height; i++)
   {
       for (int j = 0; j < Matrix.width; j++)
       {
           std::cout.width(3);
           os << Matrix.arr[i][j] << "  ";

       };
       os << std::endl;

   };
     return os;
};



template<class T>
class GaussSolve : public Matrix<T>
{

public:

    GaussSolve(int height, int width) : Matrix<T>(height, width)
    {

    };

    void printSolve() {
        for (int j = 0; j < this->width; j++)
            std::cout <<"X"<<j+1<< " = " << this->arr[0][j] << "    ";

    }

    Matrix<T> funcGaussSolve(Matrix<T> matrixToSolve)
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

                for (int k = i + 1, n = matrixToSolve.height - j - 1; n > 0; k++, n--)
                {
                    tmpstring = (-1) * Result.arr[k][j] / tmpdef;
                    for (int l = 0; l < matrixToSolve.width; l++)
                    {
                        Result.arr[k][l] = Result.arr[k][l] + Result.arr[i][l] * tmpstring;
                    };
                };
                //↑↑↑
            }
            else
            {
                //↓Смена строк если ключевой элемент равен 0↓
                if (i < tmpsize - 1)
                {
                    for (int s = 0; s < matrixToSolve.height; s++)
                    {
                        if (Result.arr[s][j] != 0)
                        {
                            int tmpswapS = 0;
                            int tmpI = s;
                            for (int j = 0; j < matrixToSolve.width; j++)
                            {

                                tmpswapS = Result.arr[tmpI][j];
                                Result.arr[i][j] = Result.arr[tmpI][j];
                                Result.arr[tmpI][j] = tmpswapS;
                            };


                        };
                    };
                };
                //↑↑↑
            }
        };
 
        for (int i = 0; i < matrixToSolve.height; i++)
        {
            for (int j = 0; j < matrixToSolve.width; j++)
            {
                if ((Result.arr[i][j] < 0.00001) && (Result.arr[i][j] > -0.00001))
                    Result.arr[i][j] = 0;
            };
        }

        Result.printExtendedMatrix();
        //↓Есть ли решения?↓
        for (int i = matrixToSolve.height - 1; i >= 0;)
        {
            int count = 0;
            for (int t = 0; t < matrixToSolve.width - 1; t++)
            {
                if (Result.arr[i][t] != 0)
                    count = 1;
            };
            if (Result.arr[i][matrixToSolve.width - 1] == 0)
                i--;
            if (i >= 0)
            {

                if ((Result.arr[i][matrixToSolve.width - 1] != 0)
                    && (count == 0))
                {
                    std::cout << "\n!!!Решений нет!!!" <<std::endl;
                    break;
                };
                if ((Result.arr[i][matrixToSolve.width - 1] != 0)
                    && (count != 0))
                    break;
            }
            else break;
        };
        //↑↑↑

        if (matrixToSolve.width == matrixToSolve.height+1)
        {
            GaussSolve<T> Solve(1, matrixToSolve.height);
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

            for (int i = tmpsize - 1, j = tmpsize - 1; i >= 0; i--, j--)
            {
                for (int k = 0; k < matrixToSolve.width - 1; k++)
                {
                    if (k != i)
                    {
                       
                        Solve.arr[0][j] = Result.arr[i][matrixToSolve.width - 1] - Result.arr[i][k];
                        Result.arr[i][matrixToSolve.width - 1] =
                            Result.arr[i][matrixToSolve.width - 1] - Result.arr[i][k];
                        Result.arr[i][k] = 0;
                      
                    }
                };
                for (int t = j - 1; t >= 0; t--)
                {
                    Result.arr[t][j] = Result.arr[t][j] * Solve.arr[0][j];
                    
                };
                Result.printExtendedMatrix();;
            };
            Result.printExtendedMatrix();
          
            std::cout << "\n Решение: \n" << std::endl;
                Solve.printSolve();
                return Solve;
        };
      
    };

};
