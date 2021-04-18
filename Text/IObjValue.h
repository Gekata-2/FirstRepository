#pragma once
//Интерфейс объектов-значений который может только создавать копию/разрушать объект 
class IObjValue 
{
public:
	virtual IObjValue* GetCopy() = 0; // создание копии
	~IObjValue() {}
};

typedef IObjValue* PIObjValue;//указатель на интерфейс