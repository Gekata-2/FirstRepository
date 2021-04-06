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
int n_s, n_l;

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
    int dir,unit;
    string st;
    char ch;
    do
    {
        gotoxy(1, 1);
        cout << ">,v,^,Home,Ins,Del,Enter,Esc";
        ch = getch();
        if (ch == ESC)
        {
            break;
        }
        if (ch != ENTER)
        {
            ch = getch();
        }
        switch (ch)
        {
        case ENTER:
            gotoxy(1, 1);
            printf("\r                                         \r");
            cout << "Line (without blanks): ";
            cin >> st;
            txt.SetCurrentLine(st);
            TextTyper(txt);
            break;
        case HOME:
            txt.GoFirstLink();
            break;
        case DOWN: txt.GoDownLink();
            break;
        case NEXT:
            txt.GoNextLink();
            break;
        case UP:
            txt.GoPrevLink();
            break;
        case INS:
            cin >> st;
            txt.SetCurrentLine(st);
            txt.InsertNextLine(st);
            TextTyper(txt);
            break;
        case DEL:
            txt.DeleteNextLine();
            break;
        
        gotoxy(1, 1);
        printf("\r                                         \r");

        cout << "Direction: 0 -Down. 1-Next";
        cin >> dir;

        gotoxy(1, 1);
        printf("\r                                         \r");

        cout << "Unit: 0 - Line, 1 - Section";
        cin >> unit;
        if (ch == INS)//вставка
        {
            cout << "Line(without blanks: ";
            cin >> st;
            if (dir == 0)
            {
                if (unit == 0)
                {
                    txt.InsertDownLine(st);
                }
                else
                {
                    txt.InsertDownSection(st);

                }
            }
            else
            {
                if (unit == 0)
                {
                    txt.InsertNextLine(st);
                }
                else
                {
                    txt.InsertNextSection(st);
                }
            }

        }
        else // удаление
        {
            if (dir == 0)
            {
                if (unit == 0)
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
    } while (ch=ESC);
}


int main(int argc,char* argv[])
{
    TAtomicTextLink::InitializationMemorySystem();
    TText txt,*pText;
    txt.Read("tt.txt");
    TextTyper(txt);
    TextProcessor(txt);
    cout << "Final Printing" << endl;
    TAtomicTextLink::GarbageCollector(txt);
    TAtomicTextLink::PrintFreeLink();
    txt.Print();
    cout << "printing by iterator" << endl;
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNextLink())
    {
        cout << txt.GetCurrentLine() << endl;
    }
	std::cout << "Hello World!\n";
    return 0;
}




