#pragma once
//��������� ��������-�������� ������� ����� ������ ��������� �����/��������� ������ 
class IObjValue 
{
public:
	virtual IObjValue* GetCopy() = 0; // �������� �����
	~IObjValue() {}
};

typedef IObjValue* PIObjValue;//��������� �� ���������