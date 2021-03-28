#pragma once
//Обработка кодов завершения
#define DATA_OK 0
#define DATA_ERROR -1

//DataCompltitionCodes является общим базовым классом
class TDataCompltitionCodes
{
protected:
	int ReturnCode;//код возврата(завершения)
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


