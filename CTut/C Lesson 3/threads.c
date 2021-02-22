#include "cclass.h"

void *functionForThread(void *args)
{

   //cast the argument into Vec2D type, because we know thats what we fed in as argument in pthread_create
   Vec2D *myPoint_pointer = (Vec2D *) args;

   //accessing argument data through pointer
   printf("Hello from thread id %d! The coordinate passed is %d, %d \n",  myPoint_pointer->id, myPoint_pointer->x, myPoint_pointer->y);

   //sleep for 2 seconds
   sleep(2);
   //modify the argument
   myPoint_pointer->x = myPoint_pointer->x + 10;
   myPoint_pointer->y = myPoint_pointer->y + 10;

   //cast it back to void* as that's what we are supposed to return 
   return (void*) myPoint_pointer;
}

int main(){

    //prepare an array of pthread_t (its thread id)
    pthread_t tid;
    pthread_t tid2;

    Vec2D point;
    point.x = 1;
    point.y = 2;
    point.id = 0;
     
    int thread_error_check = pthread_create(&tid, NULL, functionForThread, &point);

    //check error
    if (thread_error_check != 0)
    {
        perror("Failed to create thread. \n");
        exit(1);
    }

    thread_error_check = pthread_create(&tid2, NULL, functionForThread, &point);
    //check error
    if (thread_error_check != 0)
    {
        perror("Failed to create thread. \n");
        exit(1);
    }

    printf("Main thread is waiting...\n");
    void* threadReturn = NULL;

    // Second arg: the address of a variable whose content is a pointer
    // void **: address of a pointer void*
    thread_error_check = pthread_join(tid, &threadReturn); //blocks until thread returns

    if (thread_error_check != 0)
    {
        perror("Failed to join. \n");
        exit(1);
    }

    thread_error_check = pthread_join(tid2, &threadReturn); //blocks until thread returns

    if (thread_error_check != 0)
    {
        perror("Failed to join. \n");
        exit(1);
    }

    //cast it to Vec2D pointer type
    Vec2D *threadReturnPointerCasted = (Vec2D *)threadReturn;

    //print its content
    printf("A thread has terminated. The return coordinate is %d, %d \n", threadReturnPointerCasted->x, threadReturnPointerCasted->y);

}