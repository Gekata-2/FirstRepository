#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "CompletionCodesDefine.h"
#include "MainConstantsEnum.h"
#include "IObjValue.h"
#define	TEXT_LINE_LENGHT 20
#define MEMORY_SIZE		 20
#pragma warning(disable : 4996)
class TText;
class TAtomicTextLink;//класс- одна атомарное звено(строка)<--------------------<
typedef TAtomicTextLink* PTAtomicTextLink;//новый тип данных:Указатель на звено ^
typedef char TextString[TEXT_LINE_LENGHT];//TextString==char[TEXT_LINE_LENGHT]

//класс управления указателями 
class TTextPointerManagment
{
	//класс состоит из указателей не звенья(строки) в тексте
	PTAtomicTextLink p_first_link;// указатель на первое звено
	PTAtomicTextLink p_last_link; //указатель на послденее звено
	PTAtomicTextLink p_first_free_link; // указатель на первое свободное звено
	friend class TAtomicTextLink;//Благодаря тому что класс TAtomicTextLink является кентиком класса TTextMemoryManagment, 
								 //он имеет доступ к privat-членам клссса TTextMemoryManagment
};

typedef TTextPointerManagment* PTTextPointerManagment;//новый тип данных:указатель на класс управления указателями


class TAtomicTextLink : public IObjValue
{
protected:
	TextString str;// создаём строку из чаров длины TEXT_LINE_LENGHT
	PTAtomicTextLink p_next, p_down;// указатели типа звена (TAtomicTextLink) на следующий катало и на подуровень
	//система управления памятью
	static TTextPointerManagment pointer_header;
public:
	static void InitializationMemorySystem(int size=MEMORY_SIZE);//инициализация (выделения) памяти		+++
	static void PrintFreeLink(void);// печать свободных звеньев											+++
	//перегрузка операторов
	void* operator new (size_t size);//unsigned int == size_t											+++
	void operator delete (void* p_link_to_delete);//													??---				
	static void GarbageCollector(const TText& txt);//что такое константные ссылки?????					---
	//коснтруктор
	TAtomicTextLink(TextString str_to_copy  = NULL, PTAtomicTextLink p_nxt = NULL, PTAtomicTextLink p_dwn = NULL)
	{
		p_next = p_nxt;
		p_down = p_dwn;
		if (str_to_copy != NULL)
		{
			strcpy(str, str_to_copy);
		}
		else
		{
			str[0] = '\0';
		}
	}
	//деструктор
	~TAtomicTextLink()
	{
		delete[] str;
		delete p_next;
		delete p_down;
	}
	//проверка атомарности звена
	int IsAtom()
	{
		return (p_down == NULL);//если нету подуровня то вернётся true ,иначе false
	}
	//геттер на следущее звено
	PTAtomicTextLink GetNext()
	{
		return p_next;
	}
	//геттер на подуровень
	PTAtomicTextLink GetDown()
	{
		return p_down;
	}

	IObjValue* GetCopy() override
	{
		return new TAtomicTextLink(str, p_next, p_down);
	}
protected:
	//печать строки
	virtual void Print(std::ostream& os)
	{
		os << str;
	}
	friend class TText;
};


