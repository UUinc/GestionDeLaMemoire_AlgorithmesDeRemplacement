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
void InsertData(int,int,char**,char*,int);
void WipeScr_Title(void);
bool IsNumber(char);
void FormatSuiteReferences(char*);
void DisplaySuiteReferences(char*,position);

int main()
{
    int lines, colonnes;
    char W[50];
    position pos;

    char **data;

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

    //Wipe screen and write the title
    WipeScr_Title();

    //ALGORITHMES DE REMPLACEMENT
    //Insert Data depending on the algorithm used
    pos.x = 5;
    pos.y = 5;  
    //Display Suite de references W
    DisplaySuiteReferences(W, pos);

    //1. Algorithme de remplacement optimal (Algorithme de Belday)
    InsertData(lines, colonnes, data, W, 1);
    //Position where to draw the table
    pos.x = 5;
    pos.y = wherey()+2;  
    //Display the algorithme name
    gotoxy(pos.x, pos.y - 1);
    puts("Algorithme de remplacement optimal (Algorithme de Belday)");
    //Draw Table
    Table(lines, colonnes, pos);
    //Display Data
    DisplayData(lines, colonnes, pos, data);

    //2. Algorithme de remplacement FIFO
    InsertData(lines, colonnes, data, W, 2);
    //Position where to draw the table
    pos.x = 5;
    pos.y = wherey()+4;  
    //Display the algorithme name
    gotoxy(pos.x, pos.y - 1);
    puts("Algorithme de remplacement FIFO");
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
//1. Algorithme de remplacement optimal (Algorithme de Belday)
//2. Algorithme de remplacement FIFO
//3. Algorithme de remplacement LRU (Least Recently Used)
void InsertData(int lines, int colonnes, char **data, char *W, int algo)
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
            switch (algo)
            {
                case 1:
                    //algorithme optimal (belady)
                    AlgorithmeOptimal(lines, colonnes, data, W, i, j);
                    break;
                case 2:
                    //algorithme FIFO
                    AlgorithmeFIFO(lines, colonnes, data, W, i, j);
                    break;
                case 3:
                    //algorithme LRU (Least Recently Used)
                    break;
            }
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

void DisplaySuiteReferences(char *W, position pos)
{
    int i, len = strlen(W);

    gotoxy(pos.x, pos.y);

    printf("w = { ");
    for(i = 0; i < len; i++)
    {
        printf("%c", W[i]);

        if(i<len-1)
            printf(", ");
    }
    printf(" }\n");
}