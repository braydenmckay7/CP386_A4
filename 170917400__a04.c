/*
---------------------------------------------------
PROJECT - CP386 Assignment 4
FILE - 
AUTHOR - Brayden McKay (170917400) & Jordan Angst ()
VERSION - July 28th 2021
---------------------------------------------------
*/

/* IMPORTS */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int p = 5;  //number of processes
    int r = 4;  //number of resource types
    openFile("sample4_in.txt");
    int maxResources[p][r];
    int allocation[p][r];
    int available[r];
    int need[p][r];
    
}

int openFile(char* filename) {
    char content[128];
    FILE *fp;
    fp = fopen(filename,"r");
    
    if(fp == NULL) {
        printf("File not found");
        return 0;
    }
    
    while(fgets(line, sizeof(content), fp) != NULL) {
        totalCustomers++;
    }   
}
