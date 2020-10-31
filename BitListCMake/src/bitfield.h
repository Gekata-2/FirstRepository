#pragma once
#include <iostream>
#include <stdlib.h>

typedef unsigned int UINT;
class bit_field
{
private:
	int bit_length;		//длина битового поля- максимальное количество битов
	UINT* p_mem;		//память для представления битового поля
	int int_mem_lenght; //количество элементов длины int которе занимает битовое поле
	//методы реализации(прототипы)
	int get_mem_index(const int n); //получиться индекс в памяти дли n-го бита

public:
	UINT get_mem_mask(const int n); //получение битовой маски для n-го бита
	bit_field(int lenght);
	bit_field(const bit_field& bf);
	int get_length(void);			//получить длину (количество необходимых битов)
	void set_bit(const int n);		//установка бита
	void clear_bit(const int n);	//очистка бита
	int get_bit_value(const int n); //получение значения бита
	//переопребеление операторов(битовые операции)
	int operator==(const bit_field& bf);	   //сравнение
	bit_field& operator=(const bit_field& bf); //присваивание
	bit_field operator|(const bit_field& bf);  //операция "или"
	bit_field operator&(const bit_field& bf);  //операция "и"
	bit_field operator~(void);				   //отрицание
	friend std::istream& operator>>(std::istream& istr, bit_field& bf);
	friend std::ostream& operator<<(std::ostream& ostr, const bit_field& bf);
	int total_memory_usage();

	~bit_field()
	{
		delete[] p_mem;
	}
	/*
	 Структура хранения битового поля
	  битовеое поля -набор битов с номерами от 0 до bit_len
	  массив p_mem рассматривается как последовательно int_mem_leght элементво
	  биты в элементах p_mem нумеруются с права на лево (от младшых к старшим;прямой порядок)
	*/
};
