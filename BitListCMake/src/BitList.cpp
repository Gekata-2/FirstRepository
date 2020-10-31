#include <iostream>
#include "bitfield.h"

/**
конструктор ++
@param int lenght
*/
bit_field::bit_field(int lenght) : bit_length(lenght) //bit_len(lenght) тоже что и this->bit_len=lenght
{
	int_mem_lenght = (lenght + 31) >> 5; //получаем количетсво байт необходимых
	p_mem = new UINT[int_mem_lenght];	 //создаём массив из int_mem_lenght элементво

	if (p_mem != NULL)					 //если массив состоит из более чем одного элемента заполняем все эл-ты нулями
	{
		for (int i = 0; i < int_mem_lenght; i++)
		{
			p_mem[i] = 0;
		}
	}
}

/**
Конструктор копирования ++

*/
bit_field::bit_field(const bit_field& bf)
{
	bit_length = bf.bit_length;
	int_mem_lenght = bf.int_mem_lenght;
	p_mem = new UINT[int_mem_lenght];

	if (p_mem != NULL)
	{
		for (int i = 0; i < int_mem_lenght; i++)
		{
			p_mem[i] = bf.p_mem[i];
		}
	}
}

/**
Индекс int'а для n-го бита ++
*/
int bit_field::get_mem_index(const int n)
{
	//посчитать целое число int'ов разделив на 2^5
	return n >> 5; //в элементе p_mem 32 бита
}

/**
Получение битовой маски для n-го бита
*/
UINT bit_field::get_mem_mask(const int n) //битовая маска для n-го бита
{
	//преобразовать к int найти остаток от деления на 32 и сдвинуть
	return 1 << (n % 31);
}

/**
Получение длины множества (к-во битов)
*/
int bit_field::get_length(void)
{
	return bit_length;
}

/**
Установка n-го бита
*/
void bit_field::set_bit(const int n)
{
	if ((n > -1) && (n < bit_length))
	{ //применяем операцию |= к int'овому элементу для n-го бита и его маске
		p_mem[get_mem_index(n)] |= get_mem_mask(n);
	}
}

/**
Очистить n-ый бит
*/
void bit_field::clear_bit(const int n)
{


	if ((n > -1) && (n < bit_length))
	{
		p_mem[get_mem_index(n)] &= ~get_mem_mask(n);
	}
}

/**
Получить значение n-го бита
*/
int bit_field::get_bit_value(const int n)
{
	if ((n > -1) && (n < bit_length))
	{
		return p_mem[get_mem_index(n)] & get_mem_mask(n);
	}
	return 0;
}

///////////Битовые операции/////////////

/**
Присваивание
*/
bit_field& bit_field ::operator=(const bit_field& bf)
{
	std::cout << "Запустилася оператор присваивания" << std::endl;
	bit_length = bf.bit_length;				 //копируем длину в поле "длина битового поля" текущего объекта

	if (int_mem_lenght != bf.int_mem_lenght) //если поля занимают разное количество int'ов
	{
		int_mem_lenght = bf.int_mem_lenght; //присваеваем количество int'ов в текущий объект
		if (p_mem != NULL)					//если указатель на что-то указывает
		{
			delete p_mem; //удалаяем указатель
		}
		p_mem = new UINT[int_mem_lenght]; //создаём новый массив с нужным кол-вом эл-ов
	}
	if (p_mem != NULL) //если поля занимают разное кол-во int'ов и в текущем объект есть элементы
	{
		for (int i = 0; i < int_mem_lenght; i++)
		{
			p_mem[i] = bf.p_mem[i]; //копируем почленно все элементы из нужного нам объекта в текущий
		}
	}
	return *this;
}

/**
Оператор сравнения
*/
int bit_field::operator==(const bit_field& bf)
{
	std::cout << "Запустилася оператор сравнения" << std::endl;

	int result = 1;

	if (bit_length != bf.bit_length) //если у полей разное кол-во бит ,то они не равны
	{
		result = 0;
	}
	else //если количество бит одинаковое ,то почленно сравниваем каждый int
	{
		for (int i = 0; i < int_mem_lenght; i++)
		{
			if (p_mem[i] != bf.p_mem[i]) //если какие-то int'ы не равны,то поля разные
			{
				result = 0;
				break;
			}
		}
	}
	return result;
}

/**
Операция "или"
*/
bit_field bit_field::operator|(const bit_field& bf)
{
	std::cout << "Запустилася оператор <или> " << std::endl;

	int lenght = bit_length; //находим наибольшую длинну в битах и записываем её в lenght

	if (bf.bit_length > lenght)
	{
		lenght = bf.bit_length;
	}
	bit_field temp(lenght);					 //создаём объект temp с кол-вом битов lenght
	for (int i = 0; i < int_mem_lenght; i++) //копируем значения текущего объект в temp
	{
		temp.p_mem[i] = p_mem[i];
	}
	for (int i = 0; i < bf.int_mem_lenght; i++) //производим операцию побитового "или" для каждого элемента почленно
	{
		temp.p_mem[i] |= bf.p_mem[i]; //a |= b то же что и a = a | b
	}

	return temp; //возвращаем резульатат (временный объект temp)
}
/**
Операция "и"
*/
bit_field bit_field::operator&(const bit_field& bf)
{
	std::cout << "Запустилася оператор <и>" << std::endl;

	int lenght = bit_length; //находим наибольшую длинну в битах и записываем её в lenght

	if (bf.bit_length > lenght)
	{
		lenght = bf.bit_length;
	}
	bit_field temp(lenght);					 //создаём объект temp с кол-вом битов lenght
	for (int i = 0; i < int_mem_lenght; i++) //копируем значения текущего объект в temp
	{
		temp.p_mem[i] = p_mem[i];
	}
	for (int i = 0; i < bf.int_mem_lenght; i++) //производим операцию побитового "и" для каждого элемента почленно
	{
		temp.p_mem[i] &= bf.p_mem[i]; //a &= b то же что и a = a & b
	}

	return temp; //возвращаем резульатат (временный объект temp)
}

/**
Оператор "отрицание"
*/
bit_field bit_field::operator~(void)
{
	std::cout << "Запустилася оператор отрицания" << std::endl;

	int lenght = bit_length;
	bit_field temp(lenght);

	for (int i = 0; i < int_mem_lenght; i++)
	{
		temp.p_mem[i] = ~p_mem[i]; //применяем "побитовую инверсию" почленно для каждого элемента
	}
	return temp;
}
/**
Ввод
*/
std::istream& operator>>(std::istream& istr, bit_field& bf)
{
	//Формат данных-последовательность из 0 и 1 без пробелов
	//начальные пробелы игнорируются
	//при получении не 0 или 1 -завершеине ввода
	int i = 0;
	char ch = 0;
	//поиск первого эл-та(пропуск пробелов)
	{
		do
		{
			istr >> ch;
		} while (ch != ' ');
		//ввод эл-ов и включение их в множество
		while (true)
		{
			if (ch == '0')
			{
				bf.clear_bit(i++);
			}
			else if (ch == '1')
			{
				bf.set_bit(i++);
			}
			else
			{
				break;
			}
		}	
	}
	return istr;
}

/**
Вывод
*/
std::ostream& operator<<(std::ostream& ostr, bit_field& bf)
{
	//формат данных -последовательность из 0 и 1
	int lenght = bf.get_length();
	for (int i = 0; i < lenght; i++)
	{
		if (bf.get_bit_value(i))
		{
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;
}


int bit_field::total_memory_usage()
{
	std::cout <<"Total usage of memory:" <<this->int_mem_lenght*sizeof(int)<<" bytes"<<std::endl;
	return this->int_mem_lenght;
}




int main()
{
	setlocale(LC_ALL, "ru");
	int result = 0;
	bit_field A(65);
	result = A.get_length();
	std::cout << "Длина битового поля result = " << result << std::endl;

	
	A.set_bit(3);
	std::cout <<"A="<< A<<"\t(Установлен 3-ий бит)\n"<<std::endl;
	

	A.set_bit(7);
	std::cout << "A="<<A <<"\t(Установлен 7-ой бит)"<<std::endl;
	result = A.get_bit_value(7);
	std::cout << "Значение 7-го бита result = " << result <<"\n"<<std::endl;


	result = A.get_bit_value(11);
	std::cout << "Значение 11 бита result = " << result << "\n" << std::endl;
	
	A.clear_bit(7);
	result = A.get_bit_value(7);
	std::cout << "result = " << result <<"(Очищен 7-ой бит)"<< std::endl;
	std::cout <<"A="<<A << "\n" << std::endl;
	
	bit_field B(A);
	std::cout << "через оператор копирования B(A)" << std::endl;
	A.set_bit(7);
	std::cout <<"Установлен 7-ой бит A="<< A << std::endl;
	std::cout << "Сравнение A= "<<A<<" и B=" <<B<< "\n";
	if (A == B) {std::cout << "A=B<<"<< "\n\n";}
	else		{ std::cout << "A!=B" << "\n\n"; }

	bit_field C = A;
	std::cout << "через оператор присваивания (C=A)  C=" << C << std::endl;
	std::cout << "Сравнение A="<<A<<" и C="<<C<< "\n";
	if (A == C) { std::cout << "A=C" << "\n\n"; }
	else		{ std::cout << "A!=C" << "\n\n"; }
	
	B.set_bit(9);
	std::cout << "Установлен 9-ый бит B=" << B << std::endl;
	bit_field D = C | B;
	std::cout << "(D=C | B) D=" << D << " B="<<B<<", C="<<C<<std::endl;
	std::cout << "Сравнение A и D" <<" A="<<A<<", D="<<D<<"\n";
	if (A == D) { std::cout << "A=D<< std::endl"<< "\n\n"; }
	else		{ std::cout << "A!=D" << "\n\n"; }

	D = C & B;
	std::cout << "D=C&B=" << D <<" (C="<<C<<", B="<<B<<") \n";


	A.total_memory_usage();

	return 0;
}