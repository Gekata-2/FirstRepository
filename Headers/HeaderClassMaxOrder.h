#pragma once
#include <iostream>
using std::cout;
using std::cin;

class DivisionofOrders {





	private:

	int  a, max=0, count = 0;
	
	
	
	
	public:
		int maxOrder(int number)
		{
			int	x = number;

			while (x != 0)
			{
				x = x / 10;
				count++;
			};
			cout << count << std::endl;
			x = number;

			for (int i = 0; i < count - 1; i++)
			{

				a = (x % 10);
				x = x / 10;
				if (a >= max)
					max = a;

				cout << "a: " << a << std::endl;
				cout << "max:  " << max << std::endl;
			};

			




			return max;


		};



};