#pragma once
#pragma once
#include <memory>
#include <string>
#include <iostream>

#include "CompletionCodesDefine.h"
#include "MainConstantsEnum.h"
#include "IObjValue.h"
#define	TEXT_LINE_LENGHT 20
#define MEMORY_SIZE		 20

class TText;
class TAtomicTextLink;//êëàññ- îäíà àòîìàðíîå çâåíî(ñòðîêà)<--------------------<
typedef TAtomicTextLink* PTAtomicTextLink;//íîâûé òèï äàííûõ:Óêàçàòåëü íà çâåíî ^
typedef char TextString[TEXT_LINE_LENGHT];//TextString==char[TEXT_LINE_LENGHT]

//êëàññ óïðàâëåíèÿ óêàçàòåëÿìè 
class TTextPointerManagment
{
	//êëàññ ñîñòîèò èç óêàçàòåëåé íå çâåíüÿ(ñòðîêè) â òåêñòå
	 PTAtomicTextLink p_first_link;// óêàçàòåëü íà ïåðâîå çâåíî
	 PTAtomicTextLink p_last_link; //óêàçàòåëü íà ïîñëäåíåå çâåíî
	 PTAtomicTextLink p_first_free_link; // óêàçàòåëü íà ïåðâîå ñâîáîäíîå çâåíî
	friend class TAtomicTextLink;//Áëàãîäàðÿ òîìó ÷òî êëàññ TAtomicTextLink ÿâëÿåòñÿ êåíòèêîì êëàññà TTextMemoryManagment, 
								 //îí èìååò äîñòóï ê privat-÷ëåíàì êëñññà TTextMemoryManagment
	
};

typedef TTextPointerManagment* PTTextPointerManagment;//íîâûé òèï äàííûõ:óêàçàòåëü íà êëàññ óïðàâëåíèÿ óêàçàòåëÿìè


class TAtomicTextLink
{
protected:
	TextString str;// ñîçäà¸ì ñòðîêó èç ÷àðîâ äëèíû TEXT_LINE_LENGHT
	PTAtomicTextLink p_next, p_down;// óêàçàòåëè òèïà çâåíà (TAtomicTextLink) íà ñëåäóþùèé êàòàëî è íà ïîäóðîâåíü
	//ñèñòåìà óïðàâëåíèÿ ïàìÿòüþ
	
public:
	static TTextPointerManagment pointer_header;
	static void InitializationMemorySystem(int size = MEMORY_SIZE);//èíèöèàëèçàöèÿ (âûäåëåíèÿ) ïàìÿòè
	static void PrintFreeLink(void);// ïå÷àòü ñâîáîäíûõ çâåíüåâ
	//ïåðåãðóçêà îïåðàòîðîâ
	void* operator new (size_t size);//unsigned int == size_t
	void operator delete (void* p_link_to_delete);//÷òî òàêîå óêàçàòåëü íà âîéä?????
	static void GarbageCollector(const TText& txt);//÷òî òàêîå êîíñòàíòíûå ññûëêè?????
	//êîñíòðóêòîð
	TAtomicTextLink(TextString str_to_copy = NULL, PTAtomicTextLink p_nxt = NULL, PTAtomicTextLink p_dwn = NULL)
	{
		p_next = p_nxt;
		p_down = p_dwn;
		if (str_to_copy != NULL)
		{
			strcpy_s(str, str_to_copy);
		}
		else
		{
			str[0] = '\0';
		}
	}
	//äåñòðóêòîð
	~TAtomicTextLink()
	{
		//íóæíî áóäåò ðåàëèçîâàòü
	}
	//ïðîâåðêà àòîìàðíîñòè çâåíà
	int IsAtom()
	{
		return (p_down == NULL);//åñëè íåòó ïîäóðîâíÿ òî âåðí¸òñÿ true ,èíà÷å false
	}
	//ãåòòåð íà ñëåäóùåå çâåíî
	PTAtomicTextLink GetNext()
	{
		return p_next;
	}
	//ãåòòåð íà ïîäóðîâåíü
	PTAtomicTextLink GetDown()
	{
		return p_down;
	}

	void* GetCopy()
	{
		return new TAtomicTextLink(str, p_next, p_down);
	}
protected:
	//ïå÷àòü ñòðîêè
	virtual void Print(std::ostream& os)
	{
		os << str;
	}
	friend class TText;
};

