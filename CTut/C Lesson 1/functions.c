#include "cclass.h"

int main(int argc, char **argv)
{
    float output = square(3.f);
    printf("Output is %f \n", output);

    // cleared vector of v1 is located in different address as original v1
    // as it is created in the stack space of clear_vector function
    Vector v1 = {3,7,10};
    printf("Address of v1 members: 0x%llx, 0x%llx, 0x%llx\n", &v1.x, &v1.y, &v1.z);
    print_vector(v1);
    v1 = clear_vector(v1);
    print_vector(v1);

    Vector v2 = {31,99,21};
    printf("Address of v2 members: 0x%llx, 0x%llx, 0x%llx\n", &v2.x, &v2.y, &v2.z);
    print_vector(v2);
    clear_vector_byreference(&v2);
    print_vector(v2);
}

float square(float a){
   return a*a;
}

void print_vector(Vector input){
   printf("{x:%d, y:%d, z:%d}\n", input.x, input.y, input.z);
}

//**** Pass by value method of modifying created structure ****//

// Input vector is a new copy of input and thus will not affect the original.
// void clear_vector(Vector input){
//    input.x = 0;
//    input.y = 0;
//    input.z = 0;
// }

// This method or creating and destroying memory space at runtime is not efficient
Vector clear_vector(Vector input){
    printf("Address of clear_vector input members: 0x%llx, 0x%llx, 0x%llx\n", &input.x, &input.y, &input.z);
    input.x = 0;
    input.y = 0;
    input.z = 0;
    return input;
}

//**** Pass by reference method of modifying created structure ****//
void clear_vector_byreference(Vector *input){
    printf("Address of clear_vector_byreference input members: 0x%llx, 0x%llx, 0x%llx\n", &input->x, &input->y, &input->z);
    input->x = 0;
    input->y = 0;
    input->z = 0;
}
