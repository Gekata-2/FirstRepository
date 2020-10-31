#pragma once
#include <iostream>
#include <stdlib.h>

typedef unsigned int UINT;
class bit_field
{
private:
	int bit_length;		//����� �������� ����- ������������ ���������� �����
	UINT* p_mem;		//������ ��� ������������� �������� ����
	int int_mem_lenght; //���������� ��������� ����� int ������ �������� ������� ����
	//������ ����������(���������)
	int get_mem_index(const int n); //���������� ������ � ������ ��� n-�� ����

public:
	UINT get_mem_mask(const int n); //��������� ������� ����� ��� n-�� ����
	bit_field(int lenght);
	bit_field(const bit_field& bf);
	int get_length(void);			//�������� ����� (���������� ����������� �����)
	void set_bit(const int n);		//��������� ����
	void clear_bit(const int n);	//������� ����
	int get_bit_value(const int n); //��������� �������� ����
	//��������������� ����������(������� ��������)
	int operator==(const bit_field& bf);	   //���������
	bit_field& operator=(const bit_field& bf); //������������
	bit_field operator|(const bit_field& bf);  //�������� "���"
	bit_field operator&(const bit_field& bf);  //�������� "�"
	bit_field operator~(void);				   //���������
	friend std::istream& operator>>(std::istream& istr, bit_field& bf);
	friend std::ostream& operator<<(std::ostream& ostr, const bit_field& bf);
	int total_memory_usage();

	~bit_field()
	{
		delete[] p_mem;
	}
	/*
	 ��������� �������� �������� ����
	  �������� ���� -����� ����� � �������� �� 0 �� bit_len
	  ������ p_mem ��������������� ��� ��������������� int_mem_leght ���������
	  ���� � ��������� p_mem ���������� � ����� �� ���� (�� ������� � �������;������ �������)
	*/
};
