#include <iostream>
#include "MainConstantsEnum.h"
#include "AtomicTextLink.h"
#include "Text.h"
#include <conio.h>
#include "pch.h"
#include <windows.h>
using namespace std;


// gotoxy_sample.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define HOME 71
#define DOWN 80
#define NEXT 77
#define UP 72
#define ESC 27
#define INS 82
#define DEL 83
#define ENTER 13

#pragma	argsused
string strs[100];
int n_s, n_l; //количество строк и номер строкина экране

//вывод текста на экран
void TextTyper(TText& txt)
{
   clrscr();
    gotoxy(1, 2);
    txt.Print();
    n_s = 0;
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
    {
        strs[n_s++] = txt.GetCurrentLine();
    }
    txt.GoFirstLink();
    n_l = 2;
    gotoxy(1, n_l);
    cout << '\333';//текущая строка
}

void TextLineMark(TText& txt)//печать текущей строки
{
    string st = txt.GetCurrentLine();
    gotoxy(1, n_l);
    cout << " ";
    for (n_l = 0; n_l < n_s; n_l++)
    {
        if (st == strs[n_l])
        {
            break;
        }
    }
    n_l += 2;
    gotoxy(1, n_l);
    cout << "'\333";//текущая строка
}


void TextProcessor(TText& txt)
{
   int dir, unit;//dir(direction) - направление манипуляции (down/next), unit - объект манипуляции (line/section) 
   string st;//строка ,если нужно будет вставить строку 
   char ch;//принимаемый символ для манипуляции: >,v,^,Home,Ins,Del,Enter,Esc
    do
    {
        gotoxy(1, 1);
        
        cout << ">, v, ^, Home, Ins, Del, Enter, Esc";

        ch = getch();//получаем что делать


        if (ch == ESC)//выход
        {
            break;
        }
        if (ch != ENTER)//если не выходим ,то продолжаем манипуляцию 
        {
            ch = getch();
        }
         switch (ch)
         {
            case ENTER://ввод строки
                gotoxy(1, 1);
                printf("\r                                         \r");
                cout << "Line (without blanks): ";
                cin >> st;
                txt.SetCurrentLine(st);
                TextTyper(txt);
                break;
            case HOME://перемещение на корень текста
                txt.GoFirstLink();
                break;
            case DOWN: //перемещение на подуровень
                txt.GoDownLink();
                break;
            case NEXT://перемещение вперёд
                txt.GoNextLink();
                break;
            case UP://перемещение назад
                txt.GoPrevLink();
                break;
            case INS:  //если вставка или удаление то обрабатываем сложнее        
            case DEL:          
                //т.к в INS нет break; ,то при нажатии INS или DEL программа перейдёт сюда
                gotoxy(1, 1);
                printf("\r                                         \r");

                cout << "Direction: 0 - Down. 1-Next : ";//выбираем направление манипуляции
                cin >> dir;

                gotoxy(1, 1);
                printf("\r                                         \r");

                cout << "Unit: 0 - Line, 1 - Section : ";//выбираем предмет манипуляции
                cin >> unit;
           
            if (ch == INS)// если у нас вставка
            {
                gotoxy(1, 1);
                printf("\r                                         \r");

                cout << "Line(without blanks): "; //получаем строку,
                cin >> st;                        //которую нужно вставить
                    // 0 - подуровень,1 - текщий уровень
                if (dir == 0)//манипулиция с подуровнем 
                {
                        //0 - строка, 1 - раздел
                    if (unit == 0)//вставка строки (в подуровнь)
                    {
                        txt.InsertDownLine(st);
                    }
                    else//вставка раздела (в подуровень)
                    {
                        txt.InsertDownSection(st);

                    }
                }
                else//если dir != 0.То есть манипуляция со на текущем уровне
                {
                    if (unit == 0)//аналогично разделение на строку или раздел.Отличие лишь в том,что операия производится в текущем уровне
                    {
                        txt.InsertNextLine(st);
                    }
                    else
                    {
                        txt.InsertNextSection(st);
                    }
                }

            }
            else // если удаление,то аналогично.
            {
                if (dir == 0)//сначла идёт разделение на напрваление 0 - подуровень, 1 - текущий уровень
                {
                    if (unit == 0)//потом разделенеие на объект 0 - строка , 1 - уровень
                    {
                        txt.DeleteDownLine();
                    }
                    else
                    {
                        txt.DeleteDownSection();
                    }
                }
                else
                {
                    if (unit == 0)
                    {
                        txt.DeleteNextLine();

                    }
                    else
                    {
                        txt.DeleteNextSection();
                    }
                }
            }
            TextTyper(txt);
           
            break;
         }
        TextLineMark(txt);
    } while (ch != ESC);
}


int main(int argc, char* argv[])
{
    TAtomicTextLink::InitializationMemorySystem();//инициализируем и резервируем память
    TText txt, * pText;//создаём текст и указатель на текст
    txt.Read("tt.txt");//читаем текст из файла
    TextTyper(txt);//выводим текущий текст
    TextProcessor(txt);//запускаем консольный текстовый редакор
    cout << "Final Printing" << endl;//после окончания его работы выводим получившийся текст
    TAtomicTextLink::GarbageCollector(txt);//собираем мусор
    TAtomicTextLink::PrintFreeLink();      //выводим свободные строки
    txt.Print();//выводим текст
    cout << "printing by iterator" << endl;
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
    {
        cout << txt.GetCurrentLine() << endl;
    }
    std::cout << "Hello World!\n";


    return 0;
}




