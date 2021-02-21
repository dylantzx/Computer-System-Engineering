#include "cclass.h"

int main(int argc, char** argv){

    //******** Arrays ********//
    // Note that array size cannot be dynamic

    /*
    You cannot do something like this:
        int array_size = 3;
        int vector_int[array_size] = {1,2,3};
    */

    // the [] declared means that you are declaring an obejct with automatic storage duration
    // The array therefore only lives in the function
    // have to declare static if you want it to persist outside of that function but 
    // declaring static makes it fixed in size

    // To declare an array size to be determined later during runtime or that exists in the heap,
    // you have to use malloc or calloc

    int vector_int[3] = {1,2,3};
    float vector_float[3] = {0.3,0.4,0.5};
    char characters[5] = {'a','i','u','e','o'};

    printf("Contents of vector_int %d %d %d \n", vector_int[0], vector_int[1], vector_int[2]);
    printf("Contents of vector_float %f %f %f \n", vector_float[0], vector_float[1], vector_float[2]);
    printf("Contents of the second char: %c\n", characters[1]);

}