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
int safeSequence[p];

/* DECLARE FUNCTIONS */
int openFile(char* filename);

int requestResource(int customer_number, int r[]);

int releaseResource(int customer_number, int *request);

int safetyAlgorithm();

void isSafe();

void getInput();

void printAvailable();

void printMaximum();

void printAllocation();

void printNeed();

void setNeed();

int main(int argc, char *argv[])
{
	openFile("sample4_in.txt");

	printf("Number of Customers: %d\n", p);

	printf("Currently Available resources: 10 5 7 8\n");

	printMaximum();
	
	getInput();
}

int openFile(char* filename)
{
	char content[128];
	FILE *fp;
	int totalCustomers;
	fp = fopen(filename,"r");
	int max_array[20];
	int temp = 0;

	if(fp == NULL)
	{
		printf("File not found");
        	return 0;
	}

	// Fill maximum array
	for (int i = 0; i < 20; i++)
	{
		fscanf(fp, "%d,", &max_array[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			maximum[i][j] = max_array[temp];
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
	setNeed();

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
	if (safetyAlgorithm() == 0)
	{
		return -1;
	}
	
	for (int i = 0; i < p; i++)
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
    for (int i = 0; i < 4; i++)
    {
	//add available amount of resource
        available[i] += release[i];

	//subtract allocated amount for customer
        allocation[customer_number][i] -= release[i];
    }
    return 0;
}

int safetyAlgorithm(safeSequence[])
{
	int result;
	int a=0;

	result = 0;

	// set need = maximum - allocation
	setNeed();

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
				safeSequence[a++] = i;
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
	if (safetyAlgorithm() == 1)
	{
		printf("State is safe, and request is satisfied\n");
	}

	else
	{
		printf("State is not safe. Request is not satisfied\n");
	}
}

void getInput()
{
	char input[12];
	int flag = 1;
	int customer_number, count = 4;
	int request[4];

	while (flag == 1)
	{
		printf("Enter Command: ");

		fgets(input, 12, stdin);

		char *useable_input = strtok(input, "\n\r");

		if (strcmp(useable_input, "Status") == 0)
		{
			printAvailable();
			printMaximum();
			printAllocation();
			printNeed();
		}
		
		else if (strcmp(useable_input, "Run") == 0)
		{
			int valid = isSafe()
			int safeSequence[];
			
			if (valid == 1) {
				safteyAlgorithm(safeSequence[]);
				printf("Safe Sequence: ");
				for(int i=0; i<p; i++) {
					printf("%d", safeSequence[i];
				}
			}
		}

		else
		{
			//alloc_array[0 + count] = temp[5];

			printf("you entered: %s", input);
			isSafe();
		}
	}
}

void printAvailable()
{
	printf("Available Resources: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%d ", available[i]);

		if (i == 3)
		{
			printf("\n");
		}
	}
}

void printMaximum()
{
	printf("Maximum Resources: \n");
	
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

void printAllocation()
{
	printf("Allocated Resources: \n");
	
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
	printf("Need Resources: \n");

	setNeed();
	
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

void setNeed()
{
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < m; j++)
		{
			need[i][j] = maximum[i][j] - allocation[i][j];
		}
	}
}
