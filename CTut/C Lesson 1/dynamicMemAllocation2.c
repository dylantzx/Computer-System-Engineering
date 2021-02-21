#include "cclass.h"

int main(int argc, char **argv)
{
    // int *pointer = test_malloc(10);
    // printf("Returned pointer is at address 0x%llx \n", &pointer);
    // printf("Pointer is pointing to address 0x%llx \n", pointer);
    // // test print content
    // for (int i = 0; i<10; i++){
    //     printf("%d ", pointer[i]);
    // }
    // printf("\n");

    // //free the memory allocated
    // free(pointer);

    int buffersize;
    printf("Enter total number of elements: ");
    scanf("%d", &buffersize);

    //allocates memory in heap
    int *x = (int*) malloc(sizeof(char)*buffersize); //type cast it

    //initialize to some value
    printf("The original array value is : ");
    for (int i = 0; i<buffersize; i++){
        x[i] = i;
        printf("%d ", x[i]);
    }
    printf("\n");

    //pass it to the function to modofy
    modify_array(x, buffersize);

    //print its content
    printf("The new array value is : ");
    for (int i = 0; i<buffersize; i++){
        printf("%d ", x[i]);
    }   
    printf("\n");

    //free it
    free(x);
}

int* test_malloc(int size_array){
   int *x_local = malloc(sizeof(int)*size_array);
   for (int i = 0; i<size_array; i++){
       x_local[i] = i*i;
   }
   printf("Local pointer is at address 0x%llx\n", &x_local);
   printf("Pointer is pointing to address 0x%llx \n", x_local);
   return x_local;
}

void modify_array(int* array, int array_size){
   for (int i = 0; i<array_size; i++){
       array[i] += i;
    } 
}
