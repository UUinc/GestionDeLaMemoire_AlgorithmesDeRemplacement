#ifndef REPLACEMENT_ALGORITHMES_H
#define REPLACEMENT_ALGORITHMES_H

//Functions Prototype
// - algorithmes
void AlgorithmeOptimal(int,int,char**,char*,int,int);
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