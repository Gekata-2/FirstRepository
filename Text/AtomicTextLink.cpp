#include <conio.h>
#include "AtomicTextLink.h"
#include "Text.h"
using std::string;
TTextPointerManagment TAtomicTextLink::pointer_header;
//PTAtomicTextLink TAtomicTextLink::p_next;
//PTAtomicTextLink TAtomicTextLink::p_down;
//PTAtomicTextLink TAtomicTextLink::str;
using std::cout;
using std::endl;
//Инициализацтя памяти
void TAtomicTextLink::InitializationMemorySystem(int size)
{
	cout << "InitializationMemorySystem is called" << endl;
	pointer_header.p_first_link = nullptr;
	char Line[100];//строка - весь текст(состоит как бы из звеньев-строк)
	pointer_header.p_first_link = (PTAtomicTextLink) new char[sizeof(TAtomicTextLink) * size];
	/*создание строки размером=размер каждой строки*количество строк в тексте
	указатель pointer_header.p_first_link указывает на начало этой строки,а именно на структуру размером со звено TAtomicTextLink
	*/
	pointer_header.p_first_free_link = pointer_header.p_first_link;//указывает туда же куда и pointer_header.p_first_link
	pointer_header.p_last_link = pointer_header.p_first_link + (size - 1);/*указыват на последний участок текста,
	т.е. мы от указателя на превую строку перемещаемся на (size - 1) строк по тексту вперёд*/
	PTAtomicTextLink p_link = pointer_header.p_first_link;//создаём указатель типа "указатель на звено".Он указывает на начало текста,т.е на первую строку
	//размерка памяти
	for (int i = 0; i < size - 1; i++, p_link++)
	{
		p_link->p_next = p_link + 1;//p_link->p_next=(*p_link).p_nest
		/*
		Т.к p_link указывает на объект типа TAtomicTextLink,
		то при p_link->p_next мы обращаемся к полю-указателю p_next объекта TAtomicTextLink и приcваиваем ему адрес следующего объекта типа TAtomicTextLink
				___________str1__________________			___________str2__________________       ___________str3__________________
		p_link->{p_down|str|pointer_header|p_next}		--->{p_down|str|pointer_header|p_next}		--->{p_down|str|pointer_header|p_next}
											|->---------^								|->---------^								|->---------^
			На каждой итерации цикла 	p_link перемещается на следующую строку и как следствие у каждой строки есть указатель на следующую строку
		*/
	}
	p_link->p_next = NULL;//после того как мы указали всем строкам, кроме последней, где находится следующая ,указываем  последней что следующей за ней строки не существует

	//Таким образом все первичные указатели указывают на нужные конструкции и звенья
}

//печать свободных звеньев
void TAtomicTextLink::PrintFreeLink(void)
{
	//cout << "PrintFreeLink is called" << endl;

	PTAtomicTextLink p_link = pointer_header.p_first_free_link;//создаём указатель на звено и устанавливаем его на первое свободное звено
	
	for (; p_link != NULL; p_link = p_link->p_next)
	{
		//в цикле пока указатель не будет показывать на последнее звено перемещаемся по строкам последовательно
		cout << p_link->str << endl;//выводим каждую строчу
	}

}

//Выделение памяти для звена
void* TAtomicTextLink::operator new(size_t size)
{
	//cout << "new is called" << endl;
	PTAtomicTextLink p_link = pointer_header.p_first_free_link;//создаём укаатель на звено и устанавливаем на первое свободное звено
	if (pointer_header.p_first_free_link != NULL)//если  указатель на первое свободное звено не указывает на NULL,т.е существует свободное звено
	{
		//тогда переносим указатель на первое свободное звено на следующее звено,т.к это теперь будет использоваться
		pointer_header.p_first_free_link = p_link->p_next;

		/*
			|_str1_||_str2_||_str3_||______||______|								|_str1_||_str2_||_str3_||______||______|
				^				^		 ^								==>				^				^		 ^		^
			p_first_link	p_last_link  (p_first_free_link/p_link)					p_first_link   p_last_link  p_link  p_first_free_link
		
		*/
	}

	return p_link;
}

void TAtomicTextLink::operator delete(void* p_m)//принимаем указатель на какую-то область памяти 
{

	
	
	PTAtomicTextLink p_link = (PTAtomicTextLink)p_m;
	p_link->p_next = pointer_header.p_first_free_link;
	pointer_header.p_first_free_link = p_link;
}

//сборка мусора   ---
void TAtomicTextLink::GarbageCollector( TText	&txt)
{
	//пробная версия - в памяти только один текст
	string st;
	
	//маркировка строк текста - маркер "&&&"
	for (txt.Reset();!txt.IsTextEnded();txt.GoNext())
	{
		if (st.find("&&&") != 0)
		{
			txt.SetCurrentLine("&&&" + txt.GetCurrentLine());
		}
	}

	//маркировка списка свободных звеньев
	PTAtomicTextLink p_link = pointer_header.p_first_free_link;
	for (; p_link != NULL; p_link = p_link->p_next)
	{
		strcpy(p_link->str, "&&&");
	}
	//сборка мусора
	p_link = pointer_header.p_first_link;
	for (; p_link <= pointer_header.p_last_link; p_link++)
	{
		if (strstr(p_link->str, "&&&") != NULL)// строка текста или вободное звено
		{
			strcpy(p_link->str, p_link->str + 3);//снятие маркировка
		}
		else
		{
			delete p_link;//"неучтенное" звено в списке свободных
		}
	}
	
}