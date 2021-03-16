#include <conio.h>
#include "AtomicTextLink.h"
#include "Text.h"

TTextPointerManagment TAtomicTextLink::pointer_header;
using std::cout;
using std::endl;
//Инициализацтя памяти
void TAtomicTextLink::InitializationMemorySystem(int size)
{
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
	PTAtomicTextLink p_link = pointer_header.p_first_free_link;
	cout << "List of free links" << endl;
	for (; p_link!=NULL; p_link=p_link->p_next)
	{
		cout << p_link->str << endl;
	}

}