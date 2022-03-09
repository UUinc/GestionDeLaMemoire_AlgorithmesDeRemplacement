#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "console.h"
#include "table.h"
#include "remplacement_algorithmes.h"

//Functions prototype
char** ReserveData(int,int,char**);
void InsertData(int,int,char**,char*);
void WipeScr_Title(void);
bool IsNumber(char);
void FormatSuiteReferences(char*);

int main()
{
    int lines, colonnes;
    char W[50];
    position pos;

    char **data;

    //Position where to draw the table
    pos.x = 5;
    pos.y = 5;

    //Maximise Window
    MaximizeOutputWindow();

    //Wipe screen and write the title
    WipeScr_Title();

    printf("\t RAM avec cadres (cases)   : "); scanf("%d", &lines);
    printf("\t Une suite de references W : "); fflush(stdin); gets(W);

    FormatSuiteReferences(W);
    colonnes = strlen(W);
	
    //allocate memory for the 2D array
    data = ReserveData(lines, colonnes, data);

    //ALGORITHMES DE REMPLACEMENT
    //Insert Data depending on the algorithm used

    //1. Algorithme de remplacement optimal (Algorithme de Belday)
    InsertData(lines, colonnes, data, W);

    //Wipe screen and write the title
    WipeScr_Title();

    //Draw Table
    Table(lines, colonnes, pos);
    //Display Data
    DisplayData(lines, colonnes, pos, data);

    getch();
    return 0;
}
char** ReserveData(int lines, int colonnes, char **data)
{
    int i;

    data = (char**) malloc(lines * sizeof(char*));
    for(i=0; i<lines; i++)
    {
        *(data+i) = (char*) malloc(colonnes * sizeof(char));
    }

    return data;
}
void InsertData(int lines, int colonnes, char **data, char *W)
{
    int i, j, k;
	bool newResource = false;
	int mCase;
	
	int *freeCase = (int*)malloc(lines*sizeof(int));
	
    //Default Values in any type of Algorithmes de remplacement
    for(j = 0; j < colonnes && j < lines; j++)
    {
        for(i=0; i<=j && i<colonnes; i++)
        {
            *(*(data+i)+j) = W[i];
        }
        for(; i<lines && i<colonnes; i++)
        {
            *(*(data+i)+j) = ' ';
        }
    }
    //Resources Change depending on the algorithme
    for(; j<colonnes; j++)
    {
    	newResource = true;
    	
        for(i=0; i<lines; i++)
        {
            //check if the new resource exist in the Memory
            if(W[j] == *(*(data+i)+j-1))
            {
            	newResource = false;
                //copy all resources in the new cases
                for(k=0; k<lines; k++)
                {   
                    *(*(data+k)+j) = *(*(data+k)+j-1);
                }
            }
        }
        //new resource enter the RAM
        
		if(newResource)
        {
			//algorithme optimal (belady)
            AlgorithmeOptimal(lines, colonnes, data, W, i, j);
        }
    }
}
void WipeScr_Title()
{
    //wipe the screen and Write down the title
    clrscr();

    gotoxy(20, 2);
    puts("Gestion De La Memoire ( Algorithmes De Remplacement )\n\n");
}

void FormatSuiteReferences(char *W)
{
    int i, j, len = strlen(W);

    for(i=0; i<len; i++)
    {
        if(!IsNumber(W[i]))
        {
            for(j=i; j<len-1; j++)
            {
                W[j] = W[j+1];
            }
            len--;
        }
    }

    W[len] = '\0';
}

bool IsNumber(char c)
{
    switch(c)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}