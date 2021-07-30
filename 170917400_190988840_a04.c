/*
---------------------------------------------------
PROJECT - CP386 Assignment 4
FILE -
AUTHOR - Brayden McKay (170917400) & Jordan Angst (190988840)
VERSION - July 28th 2021
---------------------------------------------------
*/

/* IMPORTS */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

/* GLOBAL VARIABLES */
#define p 5  //number of processes
#define m 4  //number of resource types
int request[m]; //request array
int release[m]; //release array
int maximum[p][m];
int allocation[p][m];
int available[m];
int need[p][m];
int work[m];
int finish[p];

/* DECLARE FUNCTIONS */
int openFile(char* filename);

int requestResource(int customer_number, int r[]);

int releaseResource(int customer_number, int *request);

int safetyAlgorithm();

void isSafe();

void printMaximum();

void printAllocated();

void printNeed();

int main(int argc, char *argv[])
{
	openFile("sample4_in.txt");

	// p not printing
	printf("Number of Customers: %c\n", p);

	// not done
	printf("Currently Available resources: \n");

	printf("Maximum resources from file:\n");
	printMaximum();
}

int openFile(char* filename)
{
	char content[128];
	FILE *fp;
	int totalCustomers;
	fp = fopen(filename,"r");
	int array[20];
	int temp = 0;

	if(fp == NULL)
	{
		printf("File not found");
        	return 0;
	}

	// Fill maximum array
	for (int i = 0; i < 20; i++)
	{
		fscanf(fp, "%d,", &array[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			maximum[i][j] = array[temp];
			temp++;
		}
	}

	char line[sizeof(content)];

	while((line[sizeof(content)] = fgetc(fp)) != EOF)
	{
		if (*line == '\n')
		{
			totalCustomers++;
		}

		//in the event this line of the file is empty
		else if ((line[sizeof(content)] = fgetc(fp)) == EOF)
		{
			totalCustomers--;
		}
	}
	fclose(fp);

	return 0;
}

int requestResource(int customer_number, int r[])
{
	// set need = maximum - allocation
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < m; j++)
		{
			need[i][j] = maximum[i][j] - allocation[i][j];
		}
	}

	for (int i = 0; i < m; i++)
	{
		//if not enough customers
		if(r[i] > maximum[customer_number][i])
		{
			return -1;
		}

		//if not enough resources
		else if(r[i] > available[i])
		{
			return -1;
		}
	}

	//checks if meeting safety standards
	if(safetyAlgorithm() == 0)
	{
		return -1;
	}
	
	for(int i = 0; i < p; i++)
	{
		for (int j = 0; j < m; j++)
		{
			//add allocation to each customer
			allocation[customer_number][j] += r[i];
	    
			//subtract available amount of resource
			available[i] -= r[i];
		
			need[i][j] -= r[i];
		}
	}
	return 0;
}

int releaseResource(int customer_number, int *request)
{
    for(int i = 0; i < 4; i++)
    {
	//add available amount of resource
        available[i] += release[i];

	//subtract allocated amount for customer
        allocation[customer_number][i] -= release[i];
    }
    return 0;
}

int safetyAlgorithm()
{
	int result;

	result = 0;

	// set need = maximum - allocation
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < m; j++)
		{
			need[i][j] = maximum[i][j] - allocation[i][j];
		}
	}

	// set finish[i] to false
	// set work = available
	for (int i = 0; i < p - 1; i++)
	{
		finish[i] = 0;
		work[i] = available[i];
	}

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < m; j++)
		{
			// find i that finish[i] = false and need[i] <= work[i]
			if (finish[i] == 0 && need[i][j] <= work[i])
			{
				work[i] += allocation[i][j];
				finish[i] = 1;
			}

			else
			{
				break;
			}

			result = 1;
		}
	}

	return result;
}

void isSafe()
{
	printf("State is safe, and request is satisfied");
}

void printMaximum()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", maximum[i][j]);

			if (j == 3)
			{
				printf("\n");
			}
		}
	}
}

void printAllocated()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", allocation[i][j]);

			if (j == 3)
			{
				printf("\n");
			}
		}
	}
}

void printNeed()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", need[i][j]);

			if (j == 3)
			{
				printf("\n");
			}
		}
	}
}
