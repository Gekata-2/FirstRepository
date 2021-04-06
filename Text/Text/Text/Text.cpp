#define BUFFER_LENGHT 80
#include <conio.h>
#include "Text.h"


static char string_buffer[BUFFER_LENGHT + 1];
static int text_level;

TText::TText(PTAtomicTextLink p_l)
{
	std::cout << "TText constr"<<std::endl;
	//передаём указатель на  звено текста
	if (p_l == NULL)//если этот указатель не на какое звено не указывает
	{
		p_l = new TAtomicTextLink();//создаём звено и стави указатель на него
	}
	p_first = p_l;//присваиваем указатель на полученное звено указателю p_first 
}

//навигация

//переход к первой строке
int TText::GoFirstLink(void)
{
	std::cout << "TText GoFristLink" << std::endl;
	//очистка стека(идём по пути как бы назад: от текущей строки к первой)
	while (!path.empty())//пока стек не закончится
	{
		path.pop();//достаём из него элементы
	}

	p_current = p_first;//устанавливаем указатель на текущую строку - на первую строку,которая не пустая
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);//если вдруг оказалось что первая строка пуста,то значит с текстом что-то не так
		//устанавливаем код ошибки на ошибку
	}
	else
	{
		SetReturnCode(TEXT_OK);//если первая строка всё таки не нулевая то устанавливаем код ошибки,на то что всё хорошо
	}
	return ReturnCode;//возвращаем полученный код ошибки

}

//переход к слебующей строке по down
int TText::GoDownLink(void)
{
	std::cout << "TText GoDownLink" << std::endl;
	SetReturnCode(TEXT_ERROR_IN_TEXT);//устанавливаем код ошибки в ошибку,т.к. нам следует ещё убедиться в том что мы всё таки можем перейти на подуровень(что он существуе)
	if (p_current != NULL)//если текщая строка не нулевая
	{
		if (p_current->p_down != NULL)//если мы может опуститься на уровень
		{
			path.push(p_current);///добавяем строку на которой находимся в наш путь
			p_current = p_current->p_down;//устанавливаем указатель на текущую строку на подуровень(переходим на подуровень)
			SetReturnCode(TEXT_OK);//мы смогли перейти на подуровень,значит всё хорошо
		}
	}
	return ReturnCode;//возвращаем код ошибки
}

//переход к следующей строке по next
int TText::GoNextLink(void)
{
	return TEXT_ERROR_IN_TEXT;
}

//переход к предыдущей позиции в тексте(стеке)
int TText::GoPrevLink(void)
{
	if (path.empty())//если мы от первой стрроки не куда не перешли(т.е. стек пуст)
	{
		SetReturnCode(TEXT_NO_PREV_LINK_EXIST);//ставим код ошибки в то ,что нету предыдущего звена
	}
	else//если же мы находимся не в корне текста 
	{
		p_current = path.top();//устанавливаем текущую строку в предадущий строку(p_current не содержиться в стеке(путе))
		path.pop();//убираем верхушку стека,т.к. p_current не должен указывать на верхушку стека
		SetReturnCode(TEXT_OK);//всё хорошо
	}
	return ReturnCode;
}

//доступ

//чтение текущей строки
string TText::GetCurrentLine(void)
{
	if (p_current == NULL)//если текущая строка пустая
	{
		return string("");//возвращаем пустую строку
	}
	else//если же строка не пустая
	{
		return string(p_current->str);//возвращаем текущую строку 
	}
}

//замена текущей строки на s
void TText::SetCurrentLine(string s)
{
	if (p_current == NULL)//если текущая строка нулевая
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);//возвращаем ошибку
	}
	else//если текущая строка не нулева
	{
		strncpy(p_current->str, s.c_str(), TEXT_LINE_LENGHT);//копируем строку s в текущую str
	}
	p_current->str[TEXT_LINE_LENGHT - 1] = '\0';//???
}

//модификация

//вставка строки в подуровень
void TText::InsertDownLine(string s)
{
	if(p_current==NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else
	{
		TextString empty_str;//пустая строка исключительно для конструктора
		PTAtomicTextLink p_dwn = p_current->p_down;//создайм указатель на подуровень↓
		PTAtomicTextLink p_new = new TAtomicTextLink(empty_str, p_dwn, NULL);//создаём новое звено у которого указатель на следующий элемент равен указателю на подуровень,относительно текущего элемента
		strncpy(p_new->str, s.c_str(), TEXT_LINE_LENGHT);//заполняем новое звено строкоой s
		p_new->str[TEXT_LINE_LENGHT - 1] = '\0';//установка елси s длиннее str
		p_current->p_down = p_new;//у текущего уровня заменяем указатель на подуровень на только что созданное звено
		SetReturnCode(TEXT_OK);	
	}
}

//Вставка раздела в подуроень
void TText::InsertDownSection(string s)
{
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else
	{
		TextString empty_str;//пустая строка исключительно для конструктора
		PTAtomicTextLink p_dwn = p_current->p_down;//создайм указатель на подуровень↓
		PTAtomicTextLink p_new = new TAtomicTextLink(empty_str, NULL, p_dwn);//создаём новое звено у которого указатель на следующий элемент равен указателю на подуровень,относительно текущего элемента
		strncpy(p_new->str, s.c_str(), TEXT_LINE_LENGHT);//заполняем новое звено строкоой s
		p_new->str[TEXT_LINE_LENGHT - 1] = '\0';//установка елси s длиннее str
		p_current->p_down = p_new;//у текущего уровня заменяем указатель на подуровень на только что созданное звено
		SetReturnCode(TEXT_OK);
	}
}

//вставка строки в том же уровне
void TText::InsertNextLine(string s)
{

}

//вставка раздела в том же уровне
void TText::InsertNextSection(string s)
{

}

void TText::DeleteNextLine(void)
{

}

void TText::DeleteNextSection(void)
{

}

int TText::Reset(void)
{
	return 0;
}

int TText::IsTextEnded(void) const
{
	return 0;
}

int TText::GoNext(void)
{
	return 0;
}

void TText::Read(const char* p_file_name)
{


}

void TText::Write(char* p_file_name)
{

}
void TText::Print(void)
{

}
//удаление строки в подуровне
void TText::DeleteDownLine(void)
{
	SetReturnCode(TEXT_OK);
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else if(p_current->p_down!=NULL)
	{
		PTAtomicTextLink p_temp1 = p_current->p_down;
		PTAtomicTextLink p_temp2 = p_temp1->p_next;
		if (p_temp1->p_down == NULL)
		{
			p_current->p_down = p_temp2;
		}
	}
}



//удаление раздела в подуровень
void TText::DeleteDownSection(void)
{
	SetReturnCode(TEXT_OK);
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else if(p_current->p_down!=NULL)
	{
		PTAtomicTextLink p_temp1 = p_current->p_down;
		PTAtomicTextLink p_temp2 = p_temp1->p_next;
		p_current->p_down = p_temp2;
	}

}