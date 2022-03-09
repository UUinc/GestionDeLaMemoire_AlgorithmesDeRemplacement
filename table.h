#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdbool.h>
#include "console.h"

typedef struct
{
    int x;
    int y;
}position;

void Line(int length, bool isHorizontal)
{
    int i;

    if(isHorizontal)
    {
        printf(" ");
        //to print a simple horizontal character '\xC4' = '-'
        for(i=0; i<length; i++)
        {
            printf("\xC4");
        }
        gotoxy(wherex(), wherey()+1);
        return;
    }

    //to print a simple vertical character '\xB3' = '|'
    for(i=0; i<length; i++)
    {
        printf("\xB3");
        gotoxy(wherex()-1, wherey()+1);
    }
}

void Rect(int height, int width)
{
    position initialPos;
    initialPos.x = wherex();
    initialPos.y = wherey();

    Line(width, true);
    gotoxy(initialPos.x, wherey());
    Line(height, false);
    Line(width, true);
    gotoxy(wherex(), wherey()-1-height);
    Line(height, false);

    //setup corners
    gotoxy(initialPos.x, initialPos.y);
    printf("\xDA");
    gotoxy(initialPos.x + width + 1, initialPos.y);
    printf("\xBF");
    gotoxy(initialPos.x, initialPos.y + height + 1);
    printf("\xC0");
    gotoxy(initialPos.x + width + 1, initialPos.y + height + 1);
    printf("\xD9");

    //Position the cursor to the Right Top corner
    gotoxy(initialPos.x + width + 1, initialPos.y);
}
void SpecialRect(int height, int width, int shape)
{
    position initialPos;
    initialPos.x = wherex();
    initialPos.y = wherey();

    Line(width, true);
    gotoxy(initialPos.x, wherey());
    Line(height, false);
    Line(width, true);
    gotoxy(wherex(), wherey()-1-height);
    Line(height, false);

    //setup corners
    switch(shape)
    {
        case 1:
            //normal corners
            /*
                ┌┐
                └┘
             */
            gotoxy(initialPos.x, initialPos.y);
            printf("\xDA");
            gotoxy(initialPos.x + width + 1, initialPos.y);
            printf("\xBF");
            gotoxy(initialPos.x, initialPos.y + height + 1);
            printf("\xC0");
            gotoxy(initialPos.x + width + 1, initialPos.y + height + 1);
            printf("\xD9");
            break;
        case 2:
             /*
                ┬┐
                ┴┘
             */
            gotoxy(initialPos.x, initialPos.y);
            printf("\xC2");
            gotoxy(initialPos.x + width + 1, initialPos.y);
            printf("\xBF");
            gotoxy(initialPos.x, initialPos.y + height + 1);
            printf("\xC1");
            gotoxy(initialPos.x + width + 1, initialPos.y + height + 1);
            printf("\xD9");
            break;
        case 3:
             /*
                ┌┬
                └┴
             */
            gotoxy(initialPos.x, initialPos.y);
            printf("\xDA");
            gotoxy(initialPos.x + width + 1, initialPos.y);
            printf("\xC2");
            gotoxy(initialPos.x, initialPos.y + height + 1);
            printf("\xC0");
            gotoxy(initialPos.x + width + 1, initialPos.y + height + 1);
            printf("\xC1");
            break;
        case 4:
            /*
                ┼┼
                ┼┼
             */
            gotoxy(initialPos.x, initialPos.y);
            printf("\xC5");
            gotoxy(initialPos.x + width + 1, initialPos.y);
            printf("\xC5");
            gotoxy(initialPos.x, initialPos.y + height + 1);
            printf("\xC5");
            gotoxy(initialPos.x + width + 1, initialPos.y + height + 1);
            printf("\xC5");
            break;
    }

    //Position the cursor to the Right Top corner
    gotoxy(initialPos.x + width + 1, initialPos.y);

    //\xDA Top Left corner     '┌'
    //\xBF Top Right corner    '┐'
    //\xC0 Bottom Left corner  '└'
    //\xD9 Bottom Right corner '┘'
    //\xC2 Top corner          '┬'
    //\xC1 Bottom corner       '┴'
    //\xC5 Middle corner       '┼'
    //\xC3 Left corner         '├'
    //\xB4 Right corner        '┤'
}

void FormatingTable(int _lines, int _colonnes, position _pos)
{
    int i;
    //Set the cursor to the initial position
    //Top Left
    gotoxy(_pos.x, _pos.y);

    //Formating the up table
    for(i = 0; i <= _colonnes; i++)
    {
        if(i == 0)
        {
            printf("\xDA");
        }
        else if(i == _colonnes)
        {
            printf("\xBF");
        }
        else
        {
            printf("\xC2");
        }

        gotoxy(wherex() + 3, wherey());
    }
    //Set the cursor to the initial position
    //Bottom Left
    gotoxy(_pos.x, _pos.y + 2 * _lines);
    //Formating the bottom table
    for(i = 0; i <= _colonnes; i++)
    {
        if(i == 0)
        {
            printf("\xC0");
        }
        else if(i == _colonnes)
        {
            printf("\xD9");
        }
        else
        {
            printf("\xC1");
        }

        gotoxy(wherex() + 3, wherey());
    }
    //Set the cursor to the initial position
    //Top Left
    gotoxy(_pos.x, _pos.y);
    //Formating the Left side table
    for(i = 0; i <= _lines; i++)
    {
        if(i != 0 && i != _lines)
        {
            printf("\xC3");
        }

        gotoxy(_pos.x, wherey()+2);
    }
    //Set the cursor to the initial position
    //Top Right
    gotoxy(_pos.x, _pos.y);
    //Formating the Right side table
    for(i = 0; i <= _lines; i++)
    {
        if(i != 0 && i != _lines)
        {
            printf("\xB4");
        }

        gotoxy(_pos.x + 4 * _colonnes, wherey()+2);
    }
}
//Display Data
void DisplayData(int _lines, int _colonnes, position _pos, char** data)
{
    int i, j;
    
    gotoxy(_pos.x, _pos.y);

    for(i = 0; i < _lines; i++)
    {
        for(j = 0; j < _colonnes; j++)
        {
            gotoxy(_pos.x+2+(j*4), _pos.y+1+(i*2));
            printf("%c", *(*(data + i) + j));
        }
    }
}

void Table(int _lines, int _colonnes, position _pos)
{
    int i, j;

    gotoxy(_pos.x, _pos.y);

    for(i = 0; i < _lines; i++)
    {
        for(j = 0; j < _colonnes; j++)
        {
            //draw one simple square 1x3
            //Rect(1, 3);
            SpecialRect(1, 3, 4);
        }
        gotoxy(wherex() - (4 * _colonnes), wherey() + 2);
    }

    FormatingTable(_lines, _colonnes, _pos);
}

#endif
