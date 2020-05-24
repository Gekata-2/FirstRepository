#include <iostream>
#include <ClassMatrix.h>




int main()
{

    setlocale(LC_ALL, "ru");
    srand(time(NULL));
  

    Matrix<float> A(4,4);
    std::cout <<"A:\n"<< A<<std::endl;
    Matrix<float> B(4,4);
    std:: cout <<"B:\n"<< B << std::endl;
    Matrix<float> C=A+B;
    std::cout <<"C =A+B:\n"<< C << std::endl;
    C = A * B;
    std::cout << "C=A*B:\n" << C << std::endl;
    
    Matrix<float> D(3, 4);
   /* C = A + D;*/
  /* C = A * D;*/
    GaussSolve<float> Result(3,4);
    Matrix<float>Solve= Result.funcGaussSolve(D);

  std::cout << "" << Solve << std::endl;
   

    return 0;
};


