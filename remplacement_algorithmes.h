#ifndef REPLACEMENT_ALGORITHMES_H
#define REPLACEMENT_ALGORITHMES_H

#include "queue.h"

//Global variables
node* queue = NULL;

//Functions Prototype
// - algorithmes
void AlgorithmeOptimal(int,int,char**,char*,int,int);
void AlgorithmeFIFO(int,int,char**,char*,int,int);
// - tools
void IntializeArrayBy(int*,int,int);
int GetFreeCase(int*, int);
int CountFullCase(int*, int);

//Functions Definition
//Algorithmes
void AlgorithmeOptimal(int lines, int colonnes, char **data, char *W, int i, int j)
{
	int k;
	int mCase;
	int *freeCase = (int*)malloc(lines*sizeof(int));

	//algorithme optimal (belady)
	mCase = 0;
	IntializeArrayBy(freeCase, lines, -1);

	for(i=j+1; i<colonnes && mCase<lines-1; i++)
	{	
		for(k=0; k<lines; k++)
		{   
			if(W[i] == *(*(data+k)+j-1))
			{							
				*(freeCase + k)	= k;
				mCase = CountFullCase(freeCase, lines);
				break;
			}  
		}
	}
	
	//copy all resources in the new cases
	for(k=0; k<lines; k++)
	{   
		*(*(data+k)+j) = *(*(data+k)+j-1);
	}
	i = GetFreeCase(freeCase, lines);
	*(*(data+i)+j) = W[j];
}
void AlgorithmeFIFO(int lines, int colonnes, char **data, char *W, int i, int j)
{
	int k, value;

	//Check if the first new resource
	if(j == lines)
	{
		//by default first resources are stored in order depending on W
		for(k=0; k<lines; k++)
		{
			queue = Enqueue(queue, W[k]);
		}
	}
	//algorithme FIFO
	value = Dequeue(&queue);
	queue = Enqueue(queue, W[j]);

	//copy all resources in the new cases
	for(k=0; k<lines; k++)
	{   
		*(*(data+k)+j) = *(*(data+k)+j-1);

		if(*(*(data+k)+j-1) == value)
		{
			i = k;
		}
	}
	*(*(data+i)+j) = W[j];
}

//tools
void IntializeArrayBy(int *arr, int len, int data)
{
	int i;
	
	for(i=0; i<len; i++)
	{
		*(arr+i) = data;
	}
}

int GetFreeCase(int *arr, int len)
{
	int i;
	
	for(i=0; i<len; i++)
	{
		if(*(arr+i) == -1)
		{
			return i;
		}
	}
	
	return -1;
}

int CountFullCase(int *arr, int len)
{
	int i, c;
	
	for(i=0, c=0; i<len; i++)
	{
		if(*(arr+i) != -1)
		{
			c++;
		}
	}
	
	return c;
}
#endif