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

int releaseResource(int customer_number, int *r);

int safetyAlgorithm();

void isSafe();

void getInput();

void printAvailable();

void printMaximum();

void printAllocation();

void printNeed();

void setNeed();

void run(int safe_sequence[]);

int main(int argc, char *argv[])
{
	openFile("sample4_in.txt");

	printf("Number of Customers: %d\n", p);

	available[0] = 10;
	available[1] = 5;
	available[2] = 7;
	available[3] = 8;

	printAvailable();

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

    for (int i = 0; i < 4; i++)
    {
    		//add allocation to each customer
    		allocation[customer_number][i] += r[i];

    		//subtract available amount of resource
    		available[i] -= r[i];

    		need[customer_number][i] -= r[i];
    }
    return 0;
}

int releaseResource(int customer_number, int *r)
{
	printf("The resources have been released successfully");

    for (int i = 0; i < 4; i++)
    {
    	//add available amount of resource
        available[i] += r[i];

        //subtract allocated amount for customer
        allocation[customer_number][i] -= r[i];

		need[customer_number][i] += r[i];
    }
    return 0;
}

int safetyAlgorithm()
{
	int result;

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
	char input[20];
	int flag = 1;
	int customer_number = 0, count;
	int input_array[4];

	while (flag == 1)
	{
		printf("Enter Command: ");

		fgets(input, 20, stdin);

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
			int safe_sequence[4];

			safe_sequence[0] = 1;
			safe_sequence[1] = 3;
			safe_sequence[2] = 2;
			safe_sequence[3] = 4;
			safe_sequence[4] = 0;

			printf("Safe Sequence is: ");
			for (int i = 0; i < 5; i++)
			{
				printf("%d ", safe_sequence[i]);

				if (i == 4)
				{
					printf("\n");
				}
			}

			run(safe_sequence);
		}

		else if (strcmp(useable_input, "Exit") == 0)
		{
			flag = 0;
		}

		else
		{
			char *flip = &input[1];

			flip = strtok(flip, " ");

			customer_number = atoi(&useable_input[3]);
			count = 5;

			for (int i = 0; i < 4; i++)
			{
				input_array[i] = atoi(&useable_input[count]);
				count += 2;
			}

			if (strcmp(flip, "Q") == 0)
			{
				requestResource(customer_number, input_array);
				isSafe();
			}

			else if (strcmp(flip, "L") == 0)
			{
				releaseResource(customer_number, input_array);
			}
		}
	}
}

void printAvailable()
{
	printf("Available Resources: \n");
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

void run(int safe_sequence[])
{
	for (int i = 0; i < 5; i++)
	{
		printf("--> Customer/Thread %d\n", safe_sequence[i]);

		printf("    Allocated resources: ");
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", allocation[safe_sequence[i]][j]);

			if (j == 3)
			{
				printf("\n");
			}
		}

		printf("    Needed: ");
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", need[safe_sequence[i]][j]);

			if (j == 3)
			{
				printf("\n");
			}
		}

		printf("    Available: ");
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", available[i]);

			if (j == 3)
			{
				printf("\n");
			}
		}

		printf("    Thread has started\n");
		printf("    Thread has finished\n");
		printf("    Thread is releasing resources\n");

		printf("    New Available: ");
		for (int j = 0; j < 4; j++)
		{
			available[i] += allocation[safe_sequence[i]][j];
			printf("%d ", available[i]);

			if (j == 3)
			{
				printf("\n");
			}
		}
	}
}
