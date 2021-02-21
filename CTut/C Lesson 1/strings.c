#include "cclass.h"

int main(int argc, char** argv){

    //******** Strings ********//
    // char hello_world[12] = {'h','e','l','l','o',' ','w','o','r','l','d'};
    // printf("%s", hello_world);

    // char hello_world[12] = {'h','e','l','l','o',' ','w','o','r','l','d', '\0'};
    // printf("%s\n", hello_world);

    //allocates in a read-only portion of static memory, NOT modifiable, READ only
    // NULL termination is automatically added
    // char *hello_world_readonly = "hello world";
    // printf("%s\n", hello_world_readonly);
    // printf("Size of hello_world_better pointer %d\n",sizeof(hello_world_readonly));

    // This will allocate in the heap/stack that is modifiable during runtime
    // char hello_world_init[] = "hello world";
    // change the letter in the string
    // hello_world_init[1] = 'u';
    // printf("The new string is %s\n", hello_world_init);

    // Initialize a string by defining size to array as an empty string
    // using sprintf overwrites the entire buffer
    char sentence[BUFFERSIZE] = "";
    sprintf(sentence, "Hello World");
    printf("The sentence is: %s \n", sentence);
    sprintf(sentence, "This is another sentence overwriting the previous one. Lets write a number %d. ", 5);
    printf("The sentence now is modified to: %s \n", sentence);

    // To concatenate between strings, you can use strcat(char *dest, char *source)
    char sentence_append[64] = "The quick brown fox jumps over a lazy dog";
    strcat(sentence, sentence_append);
    printf("%s \n", sentence);

}