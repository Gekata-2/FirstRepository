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
class TAtomicTextLink;//�����- ���� ��������� �����(������)<--------------------<
typedef TAtomicTextLink* PTAtomicTextLink;//����� ��� ������:��������� �� ����� ^
typedef char TextString[TEXT_LINE_LENGHT];//TextString==char[TEXT_LINE_LENGHT]

//����� ���������� ����������� 
class TTextPointerManagment
{
	//����� ������� �� ���������� �� ������(������) � ������
	PTAtomicTextLink p_first_link;// ��������� �� ������ �����
	PTAtomicTextLink p_last_link; //��������� �� ��������� �����
	PTAtomicTextLink p_first_free_link; // ��������� �� ������ ��������� �����
	friend class TAtomicTextLink;//��������� ���� ��� ����� TAtomicTextLink �������� �������� ������ TTextMemoryManagment, 
								 //�� ����� ������ � privat-������ ������ TTextMemoryManagment
};

typedef TTextPointerManagment* PTTextPointerManagment;//����� ��� ������:��������� �� ����� ���������� �����������


class TAtomicTextLink
{
protected:
	TextString str;// ������ ������ �� ����� ����� TEXT_LINE_LENGHT
	PTAtomicTextLink p_next, p_down;// ��������� ���� ����� (TAtomicTextLink) �� ��������� ������ � �� ����������
	//������� ���������� �������
	static TTextPointerManagment pointer_header;
public:
	static void InitializationMemorySystem(int size=MEMORY_SIZE);//������������� (���������) ������
	static void PrintFreeLink(void);// ������ ��������� �������
	//���������� ����������
	void* operator new (size_t size);//unsigned int == size_t
	void operator delete (void* p_link_to_delete);//��� ����� ��������� �� ����?????
	static void GarbageCollector(const TText& txt);//��� ����� ����������� ������?????
	//�����������
	TAtomicTextLink(TextString str_to_copy  = NULL, PTAtomicTextLink p_nxt = NULL, PTAtomicTextLink p_dwn = NULL)
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
	//����������
	~TAtomicTextLink()
	{
		//����� ����� �����������
	}
	//�������� ����������� �����
	int IsAtom()
	{
		return (p_down == NULL);//���� ���� ��������� �� ������� true ,����� false
	}
	//������ �� �������� �����
	PTAtomicTextLink GetNext()
	{
		return p_next;
	}
	//������ �� ����������
	PTAtomicTextLink GetDown()
	{
		return p_down;
	}

	void* GetCopy()
	{
		return new TAtomicTextLink(str, p_next, p_down);
	}
protected:
	//������ ������
	virtual void Print(std::ostream& os)
	{
		os << str;
	}
	friend class TText;
};


