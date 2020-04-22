#include <iostream>
using std::cout;
using std::cin;

class MathExpression
{
private:int x;
public:
	int Expression(int a,int b, int f)
	{
		
		int x = (a + b - f / a) + f * a * a - (a + b);

		return x;
	};
};