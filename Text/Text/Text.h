#pragma once
#include <stack>
#include <fstream>
#include "CompletionCodesProcess.h"
#include "AtomicTextLink.h"

//Класс отвечающий за всю иерархическую структуру текаста,а не только за одно звено(строку)
using std::stack;
using std::string;

class TText;
typedef TText* PTText;

class TText : public TDataCompltitionCodes
{
protected:

//поля и методы реализации
	PTAtomicTextLink p_first;		//указатель на корень дерева(начало текста)
	PTAtomicTextLink p_current;		//указатель на текущую строку
	stack<PTAtomicTextLink> path;	//стек траектории движения по тексту(строка p_current в стек не включается)
	stack < PTAtomicTextLink > stck;
	PTAtomicTextLink GetFirstAtom(PTAtomicTextLink p_first_atom);	//поиск первого атома(строки)
	void PrintText(PTAtomicTextLink p_first_to_print);				//печать текста начиная со звена p_first_to_print
	PTAtomicTextLink ReadText(std::ifstream& txt_file);			//чтение текста из файла txt_file

public:
	
	TText(PTAtomicTextLink p_l=NULL);

	~TText()
	{
		p_first = NULL;
	}
//навигация
	int GoFirstLink(void);				//переход к первой строке
	int GoDownLink(void);				//переход к следующей строке по down(т.е. на подуровневую строку)
	int GoNextLink(void);				//переход к следующей строке по next
	int GoPrevLink(void);				//переход к предыдущей позиции в тексте
	//доступ
	string GetCurrentLine(void);		//чтение текущей строки
	void SetCurrentLine(string str);	//замена текущей строки
	//модификация 
	void InsertDownLine(string);		//вставка строки в подуровень
	void InsertDownSection(string);	//вставка раздела в подуровень
	void InsertNextLine(string);		//вставка строки в том же уровне
	void InsertNextSection(string);	//вставка раздела в том же уровне
	void DeleteDownLine(void);		//удаление строки в подуровне
	void DeleteDownSection(void);		//удаление раздела в подуровне
	void DeleteNextLine(void);		//удаление строки в том же уровне 
	void DeleteNextSection(void);		//удаление раздела в том же уровне
	//итератор 
	int Reset(void);					//установить итератор на первую строку(запись)
	int IsTextEnded(void )const;		//таблица звершена?
	int GoNext(void);					//переход к следующей записи
//работа с файлами
	void Read(char* p_file_name);		//ввод текста из файла
	void Write(char* p_file_name);		//вывод текста из файла
	//печать 
	void Print(void);					//печать текста
};

