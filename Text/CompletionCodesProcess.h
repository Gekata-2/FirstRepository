#pragma once
//Обработка кодов завершения
#define DATA_OK 0
#define DATA_ERROR -1

//DataCompltitionCodes является общим базовым классом
class TDataCompltitionCodes
{
protected:
	int return_code;//код возврата(завершения)
	int SetReturnCode(int ret)
	{
		return return_code = ret;
	}
public:
	TDataCompltitionCodes() : return_code(DATA_OK) //RetunrCode = DataOK?
	{
	
	};

	int GetRerturnCode()
	{
		int temp = return_code;
		return_code = DATA_OK;
		return temp;
	}
	virtual ~TDataCompltitionCodes()
	{
		
	};

};


