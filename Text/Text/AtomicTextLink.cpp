#include <conio.h>
#include "AtomicTextLink.h"
#include "Text.h"

TTextPointerManagment TAtomicTextLink::pointer_header;
using std::cout;
using std::endl;
//������������� ������
void TAtomicTextLink::InitializationMemorySystem(int size)
{
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
	PTAtomicTextLink p_link = pointer_header.p_first_free_link;
	cout << "List of free links" << endl;
	for (; p_link!=NULL; p_link=p_link->p_next)
	{
		cout << p_link->str << endl;
	}

}