#include "cclass.h"

int main(int argc, char** argv){
    
    float array_floats[8];
    for (int i = 0; i<8; i++){
        array_floats[i] = (float) i/8;
        printf("%f, ", array_floats[i]);
    }
    printf("\n");

    int i = 0;
    while(i < 8){
        array_floats[i] += 0.5f;
        printf("%f, ", array_floats[i]);
        i ++;
    }
    printf("\n");

    i = 0;
    do{
        array_floats[i] -= 0.5f;
        printf("%f, ", array_floats[i]);
        i ++;
    }while(i<8);
    printf("\n");

    
}