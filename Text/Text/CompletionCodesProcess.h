#pragma once
//��������� ����� ����������
#define DATA_OK 0
#define DATA_ERROR -1

//DataCompltitionCodes �������� ����� ������� �������
class TDataCompltitionCodes
{
protected:
	int ReturnCode;//��� ��������(����������)
	int SetReturnCode(int ret)
	{
		return ReturnCode = ret;
	}
public:
	TDataCompltitionCodes() : ReturnCode(DATA_OK) //RetunrCode = DataOK?
	{
	
	};

	int GetRerturnCode()
	{
		int temp = ReturnCode;
		ReturnCode = DATA_OK;
		return temp;
	}
	virtual ~TDataCompltitionCodes()
	{
		
	};

};


