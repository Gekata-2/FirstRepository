#define BUFFER_LENGHT 80
#include <conio.h>
#include "Text.h"
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

static char string_buffer[BUFFER_LENGHT + 1];
static int text_level;

TText::TText(PTAtomicTextLink p_l)
{
	
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
	//std::cout << "TText GoFristLink" << std::endl;
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
	return return_code;//возвращаем полученный код ошибки

}

//переход к слебующей строке по down
int TText::GoDownLink(void)
{
	//std::cout << "TText GoDownLink" << std::endl;
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
	return return_code;//возвращаем код ошибки
}

//переход к следующей строке по next
int TText::GoNextLink(void)
{
	SetReturnCode(TEXT_ERROR_IN_TEXT);
	if (p_current != NULL)
	{
		if (p_current->p_next != NULL)
		{
			path.push(p_current);
			p_current = p_current->p_next;
			SetReturnCode(TEXT_OK);
		}
	}
	
	return return_code;
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
	return return_code;
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
		PTAtomicTextLink p_new = new TAtomicTextLink(empty_str,p_dwn,NULL);//создаём новое звено у которого указатель на следующий элемент равен указателю на подуровень,относительно текущего элемента
		p_new->p_next = p_dwn;//приходиться заполнять вручную,т.к. конструктор почему-то не заполняет
		p_new->p_down = NULL;
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

		PTAtomicTextLink p_new = new TAtomicTextLink(empty_str,NULL,p_dwn);//создаём новое звено у которого указатель на следующий элемент равен указателю на подуровень,относительно текущего элемента
		p_new->p_next = NULL;//приходиться заполнять вручную,т.к. конструктор почему-то не заполняет
		p_new->p_down = p_dwn;
		strncpy(p_new->str, s.c_str(), TEXT_LINE_LENGHT);//заполняем новое звено строкоой s
		p_new->str[TEXT_LINE_LENGHT - 1] = '\0';//установка елси s длиннее str
		
		p_current->p_down = p_new;//у текущего уровня заменяем указатель на подуровень на только что созданное звено
		SetReturnCode(TEXT_OK);
	}
}

//вставка строки в том же уровне
void TText::InsertNextLine(string s)
{
	
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else
	{
		TextString empty_str;
		PTAtomicTextLink p_d = p_current->p_next;
		
		PTAtomicTextLink p_l = new TAtomicTextLink(empty_str,p_d,NULL);
		p_l->p_next = p_d;//приходиться заполнять вручную,т.к. конструктор почему-то не заполняет
		p_l->p_down = NULL;
		strncpy(p_l->str, s.c_str(), TEXT_LINE_LENGHT);	
		p_l->str[TEXT_LINE_LENGHT - 1] = '\0';//установа если s длиннее str

		p_current->p_next = p_l;//установка указателя на новую строку
		SetReturnCode(TEXT_OK);
	}
}

//вставка раздела в том же уровне
void TText::InsertNextSection(string s)
{
	
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else
	{
		
		TextString empty_str;
		PTAtomicTextLink p_d = p_current->p_next;
		
		PTAtomicTextLink p_l = new TAtomicTextLink(empty_str,NULL,p_d);
		p_l->p_next = NULL;//приходиться заполнять вручную,т.к. конструктор почему-то не заполняет
		p_l->p_down = p_d;
		strncpy(p_l->str, s.c_str(), TEXT_LINE_LENGHT);
		p_l->str[TEXT_LINE_LENGHT - 1] = '\0';//установа если s длиннее str

		p_current->p_next = p_l;//установка указателя на новую строку
		SetReturnCode(TEXT_OK);
	}
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

//удаление строки в том же уровне
void TText::DeleteNextLine(void)
{
	SetReturnCode(TEXT_OK);
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else if(p_current->p_next!=NULL)
	{
		PTAtomicTextLink p_l1 = p_current->p_next;
		PTAtomicTextLink p_l2 = p_l1->p_next;
		if (p_l1->p_down == NULL)//только для атома
		{
			p_current->p_next = p_l2;
		}
	}
}

//удаление раздела в том же уровне
void TText::DeleteNextSection(void)
{
	SetReturnCode(TEXT_OK);
	if (p_current == NULL)
	{
		SetReturnCode(TEXT_ERROR_IN_TEXT);
	}
	else if (p_current->p_next != NULL)
	{
		PTAtomicTextLink p_l1 = p_current->p_next;
		PTAtomicTextLink p_l2 = p_l1->p_next;
		p_current->p_next = p_l2;		
	}

}


//установить на первую запись
int TText::Reset(void)
{
	//очистка стека
	while (!stck.empty())
	{
		stck.pop();
	}
	//текущая строка в стеке не храниться
	//исключение - первая страка текста,которая на дне стека
	p_current = p_first;
	if (p_current != NULL)
	{
		stck.push(p_current);
		if (p_current->p_next != NULL)
		{
			stck.push(p_current->p_next);
		}
		if (p_current->p_down != NULL)
		{
			stck.push(p_current->p_down);
		}
	}
	return IsTextEnded();
}

//таблица завершена?
int TText::IsTextEnded(void) const
{
	return !stck.size();
}

int TText::GoNext(void)
{
	if (!IsTextEnded())
	{
		//если после выборки стек пуст,значит первая строка текста уже была обработана
		p_current = stck.top();
		stck.pop();
		if (p_current != p_first)
		{
			if (p_current->p_next != NULL)
			{
				stck.push(p_current->p_next);
			}
			if (p_current->p_down != NULL)
			{
				stck.push(p_current->p_down);
			}
		}

	}
	return IsTextEnded();
}

//копирование текста

//поиск первого атома
PTAtomicTextLink TText::GetFirstAtom(PTAtomicTextLink p_l)
{
	PTAtomicTextLink temp = p_l;
	while (!temp->IsAtom())
	{
		stck.push(temp);
		temp = temp->GetDown();

	}
	return temp;
}


//копирование текста
PTText TText::GetCopy()
{
	PTAtomicTextLink p_line1, p_line2, p_line, curr_p_line;
	p_line = p_first;
	TextString copy_str = "Copy";
	curr_p_line = NULL;
	if (p_first != NULL)
	{
		while (!stck.empty())
		{
			stck.pop();
		}
		while (1)
		{
			if (p_line != NULL)
			{
				p_line = GetFirstAtom(p_line);
				stck.push(p_line);
				p_line = p_line->GetDown();
			}
			else if (stck.empty())
			{
				break;
			}
			else
			{
				p_line1 = stck.top();
				stck.pop();
				if (strstr(p_line1->str, "Copy") == NULL)
				{
					p_line2 = new TAtomicTextLink(copy_str, p_line1, curr_p_line);
					stck.push(p_line2);
					p_line = p_line1->GetNext();
					curr_p_line = NULL;
				}
				else
				{
					p_line2 = p_line1->GetNext();
					strcpy(p_line1->str, p_line2->str);
					p_line1->p_next = curr_p_line;
					curr_p_line = p_line1;
				}
			}
			
		}
	}
	return new TText(curr_p_line);
}

//печать текста
void TText::Print()
{
	int text_level = 0;
	PrintText(p_first);
}

void TText::PrintText(PTAtomicTextLink p_text_line)
{
	if (p_text_line != NULL)
	{
		/*std::cout << "next pointer:" << p_text_line->GetNext() << " down pointer:" << p_text_line->GetDown();*/
		for (int i = 0; i < text_level; i++)
		{
			std::cout << " ";
		}
	
		std::cout << " " << p_text_line->str << std::endl;
		text_level++;
		PrintText(p_text_line->GetDown());
		text_level--;
		PrintText(p_text_line->GetNext());
	}

}


//чтение текста из файла
void TText::Read(const char* p_file_name)
{
	std::ifstream txt_file(p_file_name);
	text_level = 0;
	char tmp_string[1000];
	
	std::ifstream in(p_file_name, std::ios::in); // окрываем файл для чтения

	std::stringstream sstr;
	sstr << in.rdbuf();
	
	std::cout << sstr.str();
	if (txt_file.is_open())
	{
		p_first = ReadText(txt_file);
	}
}

PTAtomicTextLink TText::ReadText(std::ifstream &txt_file)
{
	PTAtomicTextLink p_head, p_text_line;
	p_head = p_text_line = new TAtomicTextLink();
	string tmp_string;
	
	while (txt_file.eof() == 0)
	{
		
		txt_file.getline(string_buffer, BUFFER_LENGHT, '\n');
		std::cout << "string_buffer" << string_buffer << std::endl;
		if (string_buffer[0]=='}')
		{
			text_level--;
			break;
		}
		else if (string_buffer[0] == '{')//рекурсия
		{
			text_level++;
			p_text_line->p_down = ReadText(txt_file);
		}
		else//присоединение следующей строки
		{
			p_text_line->p_next = new TAtomicTextLink(string_buffer, NULL, NULL);
			p_text_line = p_text_line->p_next;
		}
	}
	p_text_line = p_head;
	if (p_head->p_down == NULL)//удаление первой строки,если нет подуровня
	{
		p_head = p_head->p_next;
		delete p_text_line;
	}
	return p_head;
}