#include "cclass.h"

int main(int argc, char **argv)
{
    // Segmentation fault happens when you try to access a memory location
    // that has not been allocated to you yet
    int buffersize;
    printf("Enter total number of elements: ");
    // Value of integer is stored in the address 
    scanf("%d", &buffersize);

    // POINTER AND SIZE COMES TOGETHER

    //allocates memory in heap
    int *x = (int*) malloc(sizeof(int)*buffersize); //type cast it
    //print the address x is pointing to
    printf("Memory address allocated by malloc starts at 0x%llx\n", x);
    //print the address of the pointer x
    printf("This pointer is stored at address 0x%llx\n", &x);

    // do something with the array
    for (int i = 0; i<buffersize; i++){
        x[i] = i;
    }

    printf("Enter additional number of elements: ");
    scanf("%d", &buffersize);

    //resize the array, buffersize can be smaller than original amount. The remainder is automatically freed
    //the unused memory initially pointed by x is also automatically freed
    int *y = realloc(x, buffersize);
    printf("Memory address allocated by realloc starts at 0x%llx\n", y);
    printf("This new pointer is stored at address 0x%llx\n", &y);
    for (int i = 0; i<buffersize; i++){
        printf("Original content element %d is %d \n", i, x[i]);
        x[i] += i; //do something with the array
    }

    //free heap manually
   free(y);
}