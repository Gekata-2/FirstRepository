#pragma once
#include <stack>
#include <fstream>
#include "CompletionCodesProcess.h"
#include "AtomicTextLink.h"

//����� ���������� �� ��� ������������� ��������� �������,� �� ������ �� ���� �����(������)
using std::stack;
using std::string;

class TText;
typedef TText* PTText;

class TText : public TDataCompltitionCodes
{
protected:

//���� � ������ ����������
	PTAtomicTextLink p_first;		//��������� �� ������ ������(������ ������)
	PTAtomicTextLink p_current;		//��������� �� ������� ������
	stack<PTAtomicTextLink> path;	//���� ���������� �������� �� ������(������ p_current � ���� �� ����������)
	stack < PTAtomicTextLink > stck;
	PTAtomicTextLink GetFirstAtom(PTAtomicTextLink p_first_atom);	//����� ������� �����(������)
	void PrintText(PTAtomicTextLink p_first_to_print);				//������ ������ ������� �� ����� p_first_to_print
	PTAtomicTextLink ReadText(std::ifstream& txt_file);			//������ ������ �� ����� txt_file

public:
	
	TText(PTAtomicTextLink p_l=NULL);

	~TText()
	{
		p_first = NULL;
	}
//���������
	int GoFirstLink(void);				//������� � ������ ������
	int GoDownLink(void);				//������� � ��������� ������ �� down(�.�. �� ������������ ������)
	int GoNextLink(void);				//������� � ��������� ������ �� next
	int GoPrevLink(void);				//������� � ���������� ������� � ������
	//������
	string GetCurrentLine(void);		//������ ������� ������
	void SetCurrentLine(string str);	//������ ������� ������
	//����������� 
	void InsertDownLine(string);		//������� ������ � ����������
	void InsertDownSection(string);	//������� ������� � ����������
	void InsertNextLine(string);		//������� ������ � ��� �� ������
	void InsertNextSection(string);	//������� ������� � ��� �� ������
	void DeleteDownLine(void);		//�������� ������ � ���������
	void DeleteDownSection(void);		//�������� ������� � ���������
	void DeleteNextLine(void);		//�������� ������ � ��� �� ������ 
	void DeleteNextSection(void);		//�������� ������� � ��� �� ������
	//�������� 
	int Reset(void);					//���������� �������� �� ������ ������(������)
	int IsTextEnded(void )const;		//������� ��������?
	int GoNext(void);					//������� � ��������� ������
//������ � �������
	void Read(char* p_file_name);		//���� ������ �� �����
	void Write(char* p_file_name);		//����� ������ �� �����
	//������ 
	void Print(void);					//������ ������
};

