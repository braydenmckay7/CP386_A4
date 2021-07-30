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

#define p 5  //number of processes
#define m 4  //number of resource types
int request[m]; //request array
int release[m]; //release array
int maximum[p][m];
int allocation[p][m];
int available[m];
int need[p][m];
    
int main(int argc, char *argv[]) {
    openFile("sample4_in.txt");
   
}

int openFile(char* filename) {
    char content[128];
    FILE *fp;
    int totalCustomers;
    fp = fopen(filename,"r");
    
    if(fp == NULL) {
        printf("File not found");
        return 0;
    }
    
    char line[sizeof(content)];
    while(fgets(line, sizeof(content), fp) != NULL) {
        totalCustomers++;
    }   
}

int requestResource(int customer_number, int r) {
    for(int i=0; i < 4; i++) {
        if(r[i] > maximum[customer_number][i]){ //if not enough customers
            return -1;
        }
        else if(r[i] > available[i]){   //if not enough resources
            return -1;
        }
    }
    
    if(!safetyAlgorithm(customer_number, r)) {   //checks if meeting saftey standards
        return -1;
    }
    
    for(int i=0; i < 4; i++) {
        allocation[customer_number][i] += r[i]; //add allocation to each customer
        available[i] -= r[i];   //subtract available amount of resource
    }
    return 0;
}

int releaseResource(int customer_number, int *request) {
    for(int i=0; i < 4; i++){
        available[i] += release[i];  //add available amount of resource
        allocation[customer_number][i] -= release[i]; //subtract allocated amount for customer
    }
    return 0;
}

int safetyAlgorithm(int customer_number, int *r) 
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
		// find i that finish[i] = false and need[i] <= work[i]
		if (finish[i] == 0 && need[i] <= work[i])
		{
			work = work + allocation[i];
			finish[i] = 1;
		}

		else
		{
			break;
		}

		result = 1;
	}

	return result;
}

void isSafe()
{
    printf("State is safe, and request is satisfied");    
}
