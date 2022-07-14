#include <stdio.h>
#include <stddef.h>
#include "mergesort.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

// author @ Cavin Gada

int main(int argc, char *argv[]) {


    bool isInt = false;  // keeps track of whether we will process in int/double

    // see if int or double input
    if (strcmp(argv[1], "-i") == 0) {
        isInt = true;
    }
    if (strcmp(argv[1],"-d") == 0) {
        isInt = false;
    }

    // get file name
    const char* fileName = argv[2];

    FILE* fp = fopen(fileName, "r"); //open file

    int i = 0; //this will keep track of length
    
    if (!isInt) { // this branch is for double input
        double* array = malloc(1024); // allocate malloc of max lines 1024

        double val;

        while(fscanf(fp, "%lf", &val) != EOF) { // read numbers line by line until end of file
            array[i] = val;
            i++;
        }
        mergesort(array,i,sizeof(double),dbl_cmp); // call mergesort on the double array
        for (int j = 0; j<i; j++) {
            printf("%lf\n", array[j]);          // print out the values by indexing through the array, knowing i is the length
        }
        free(array);                            // free memory used
    }
    else { //same exact thing as the double, except in terms of int. Syntax very similar. 
        int* array = malloc(1024); 

        long int val;

        while(fscanf(fp, "%ld", &val) != EOF) {
            array[i] = val;
            i++;
        }
        mergesort(array,i,sizeof(int),int_cmp);
        for (int j = 0; j<i; j++) {
            printf("%d\n", array[j]);
        }
        free(array); 
    }
    fclose(fp);
    return 0;
}