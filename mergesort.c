#include <stdio.h>
#include <stddef.h>
#include "mergesort.h"
#include <stdlib.h>
// author @ Cavin Gada

/* Functions to compare a and b */
int int_cmp(const void* a, const void* b) {
    
    int i_a = *(int*) a;        // cast from void pointer to int
    int i_b = *(int*) b;

    if (i_a > i_b) {            // if first number > second, return 1
        return 1;
    }
    if (i_a == i_b) {           // if equal, return 0
        return 0;
    }
    else {                      // if first numbe r< second, return -1
        return -1;
    }
}
int dbl_cmp(const void* a, const void* b){

    double d_a = *(double*) a;
    double d_b = *(double*) b;

    if (d_a > d_b) {
        return 1;
    }
    if (d_a == d_b) {
        return 0;
    }
    else {
        return -1;
    }
}

/*
This function copies the contentions of void*a to void*b. 
*/
void move(void* a, void* b, int elem_sz) { 
    char *pa = (char*)a;            // cast void pointers to char pointers as shown in class
    char *pb = (char*)b;
    
    for (int i = 0; i<elem_sz; i++) {   // loop through each byte of the int/double by incrementing char pointer by 1 (until the total bytes for the type)
        *(pb+i) = *(pa+i);              // assign each byte of b to each byte of a for the value we are looping over. 
    }
}

/*
This is the mergesort helper function. In this we will keep track of the following:
void* array - the address of the first element in the original array
void* scratch - the address of the first element in the new/"scratch" array in which we will copy elements from array
int low - the index of the lower bound we are operating from
int high - the index of the upper bound we are operating until
size_t elem_sz - the number of bytes for the type we are dealing with (8 for double, 4 for int)
int (*comp)(const void*, const void*) - pointer to the compare function we are using (int or double compare)
*/
void mergesort_h(void* array, void* scratch, int low, int high, size_t elem_sz, int (*comp)(const void*, const void*)) {
	//base case. we exit once the merging is complete
	if (low >= high) {
		return;
	}
	
    if (low < high) {
        // calculate midpoint of current section of array
    	int mid = low + (high-low)/2;

        // recursive calls to the left and right branches, respectively
    	mergesort_h(array, scratch, low, mid, elem_sz, comp); // low to mid is the left
    	mergesort_h(array, scratch, mid+1, high, elem_sz, comp); //mid+1 to high is the right

    	// store variables that keep track of necessary indices for comparison.
    	int i1 = low;   // used on left half
    	int i2 = mid+1; // used on right half
    	int i = low;
        
        // have array stored as a char* so we can keep track of current elements
        char *array_char = array;
        char *scratch_char = scratch;

        // store the three positions we need to begin copying
        void *elem1, *elem2, *scratch_pos;

        // we don't want to go out of bounds of our segments
    	while (i1 <= mid && i2 <= high) {

            elem1 = array_char + i1*elem_sz;        // this will give current elem address.
            elem2 = array_char + i2*elem_sz;        // multiply by elem size to offset the correct # bytes
            scratch_pos = scratch_char + i*elem_sz;

            if (comp(elem1, elem2)<=0) {            // case 1: elem1 <= elem2, then we want to move elem 1 in first.
                move(elem1,scratch_pos, elem_sz);
                i++;                                // update our positions
                i1++;
            }
            else {                                  // case 2: elem 1 > elem2, then we want to move elem 2 in first.
                move(elem2,scratch_pos, elem_sz);
                i++;
                i2++;
            }
    	}
        for (int j = i1; j<= mid; j++) {            // if there are leftover elements (left), copy over (uneven split)
            elem1 = array_char + i1*elem_sz;
            elem2 = array_char + i2*elem_sz;

            scratch_pos = scratch_char + i*elem_sz;

            move(elem1, scratch_pos, elem_sz);
            i++;
            i1++;
            
    	}

        for (int j2 = i2; j2<=high; j2++){          // same as previous, except for right
            elem1 = array_char + i1*elem_sz;
            elem2 = array_char + i2*elem_sz;

            scratch_pos = scratch_char + i*elem_sz;
            move(elem2, scratch_pos, elem_sz);
            i++;
            i2++;
    	}
        
    	//copy scratch to array, so we don't lose track of our progress.

    	for (int k = low; k<=high; k++) {
    		move(scratch+elem_sz*k, array+elem_sz*k, elem_sz);
    	}
        
    }
    return;
}

/* Main sorting algorithm you need to implement */
void mergesort(void*  array,
               size_t len,
               size_t elem_sz,
               int (*comp)(const void*, const void*)) {

    if (len == 0 || len == 1) return;           // an empty array or an array of 1 element should just return the array.
    void* scratch = malloc(elem_sz*len);        // create the scratch array, initialize it to the only required space (length*#ofbytes)
    
    mergesort_h(array, scratch, 0, len-1, elem_sz, comp); // call mergesort, where low is the beginning index, 0
    free(scratch);                                        // high is the last index (len-1). elem_sz is the number of bytes for the type and
    return;                                               // comp is the type of compare we use (int/double)
}
