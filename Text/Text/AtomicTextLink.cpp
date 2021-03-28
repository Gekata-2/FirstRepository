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
//������������� ������
void TAtomicTextLink::InitializationMemorySystem(int size)
{
	cout << "InitializationMemorySystem is called" << endl;
	pointer_header.p_first_link = nullptr;
	char Line[100];//������ - ���� �����(������� ��� �� �� �������-�����)
	pointer_header.p_first_link = (PTAtomicTextLink) new char[sizeof(TAtomicTextLink) * size];
	/*�������� ������ ��������=������ ������ ������*���������� ����� � ������
	��������� pointer_header.p_first_link ��������� �� ������ ���� ������,� ������ �� ��������� �������� �� ����� TAtomicTextLink
	*/
	pointer_header.p_first_free_link = pointer_header.p_first_link;//��������� ���� �� ���� � pointer_header.p_first_link
	pointer_header.p_last_link = pointer_header.p_first_link + (size - 1);/*�������� �� ��������� ������� ������,
	�.�. �� �� ��������� �� ������ ������ ������������ �� (size - 1) ����� �� ������ �����*/
	PTAtomicTextLink p_link = pointer_header.p_first_link;//������ ��������� ���� "��������� �� �����".�� ��������� �� ������ ������,�.� �� ������ ������
	//�������� ������
	for (int i = 0; i < size - 1; i++, p_link++)
	{
		p_link->p_next = p_link + 1;//p_link->p_next=(*p_link).p_nest
		/*
		�.� p_link ��������� �� ������ ���� TAtomicTextLink,
		�� ��� p_link->p_next �� ���������� � ����-��������� p_next ������� TAtomicTextLink � ���c������� ��� ����� ���������� ������� ���� TAtomicTextLink
				___________str1__________________			___________str2__________________       ___________str3__________________
		p_link->{p_down|str|pointer_header|p_next}		--->{p_down|str|pointer_header|p_next}		--->{p_down|str|pointer_header|p_next}
											|->---------^								|->---------^								|->---------^
			�� ������ �������� ����� 	p_link ������������ �� ��������� ������ � ��� ��������� � ������ ������ ���� ��������� �� ��������� ������
		*/
	}
	p_link->p_next = NULL;//����� ���� ��� �� ������� ���� �������, ����� ���������, ��� ��������� ��������� ,���������  ��������� ��� ��������� �� ��� ������ �� ����������

	//����� ������� ��� ��������� ��������� ��������� �� ������ ����������� � ������
}

//������ ��������� �������
void TAtomicTextLink::PrintFreeLink(void)
{
	cout << "PrintFreeLink is called" << endl;

	PTAtomicTextLink p_link = pointer_header.p_first_free_link;//������ ��������� �� ����� � ������������� ��� �� ������ ��������� �����
	cout << "List of free links" << endl;
	for (; p_link != NULL; p_link = p_link->p_next)
	{
		//� ����� ���� ��������� �� ����� ���������� �� ��������� ����� ������������ �� ������� ���������������
		cout << p_link->str << endl;//������� ������ ������
	}

}

//��������� ������ ��� �����
void* TAtomicTextLink::operator new(size_t size)
{
	cout << "new is called" << endl;
	PTAtomicTextLink p_link = pointer_header.p_first_free_link;//������ �������� �� ����� � ������������� �� ������ ��������� �����
	if (pointer_header.p_first_free_link != NULL)//����  ��������� �� ������ ��������� ����� �� ��������� �� NULL,�.� ���������� ��������� �����
	{
		//����� ��������� ��������� �� ������ ��������� ����� �� ��������� �����,�.� ��� ������ ����� ��������������
		pointer_header.p_first_free_link = p_link->p_next;

		/*
			|_str1_||_str2_||_str3_||______||______|								|_str1_||_str2_||_str3_||______||______|
				^				^		 ^								==>				^				^		 ^		^
			p_first_link	p_last_link  (p_first_free_link/p_link)					p_first_link   p_last_link  p_link  p_first_free_link
		
		*/
	}

	return p_link;
}

void TAtomicTextLink::operator delete(void* p_m)//��������� ��������� �� �����-�� ������� ������ 
{
	cout << "delete is called" << endl;
	free(p_m);
	//PTAtomicTextLink p_link = static_cast<PTAtomicTextLink>(p_m);
	//delete p_link->p_down;
	//delete p_link->p_next;
	//delete[] p_link->str;
}

//������ ������   ---
void TAtomicTextLink::GarbageCollector(const TText& txt)
{
	//������� ������ - � ������ ������ ���� �����
	string st;

	//���������� ����� ������ - ������ "&&&"
	for (size_t i = 0; i < 1; i++)
	{

	}
}