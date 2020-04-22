#pragma once
using namespace std;
class Matrix {

 int height;
 int width;

public:
    int** arr;
    // asdsadsadasd;
    
    Matrix(int height, int width)
    {
        cout << "Вызвался конструктор: " << this << endl;
        cout << "\n";
        this->height = height;
        this->width = width;
        arr = new int* [this->height];
        for (int i = 0; i < this->height; i++)
            arr[i] = new int[width];

        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                arr[i][j] = 1;
               
            };
          
        };
        cout << endl;
    }

        Matrix operator+(const Matrix& SecondMatrix) 
        {
         /* cout << SecondMatrix.arr<<endl;*/
            cout << "Вызвалася опреатор сложения матриц: " << this << endl;
            Matrix Result(this->height, this->width);
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    Result.arr[i][j] = this->arr[i][j]+SecondMatrix.arr[i][j];
                    cout << Result.arr[i][j] << " ";

                };
                cout << endl;
            };
            return Result;

        }
         
        Matrix& operator=(const Matrix &SecondMatrix)
            {
                cout << "Вызвалася опреатор присваивания матриц: " << this << endl;
                this->height = SecondMatrix.height;
                this->width = SecondMatrix.width;
               
                for (int i = 0; i < this->height; i++)
                    delete[] this->arr[i];
                delete[] this->arr;
              
               this-> arr = new int* [this->height];
                for (int i = 0; i < this->height; i++)
                    this->arr[i] = new int[SecondMatrix.width];

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
            cout << "Вызвалася опреатор умножения матриц: C " << this << endl;

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
            cout << "Вызвалась функция printMatrix: " << this << endl;
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                    cout << arr[i][j] << " ";
                cout << endl;
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