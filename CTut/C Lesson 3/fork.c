#include "cclass.h"

int child_process_function(int* array, int size, int id){

   printf("Hello from child number %d with pid %d!\n", id, getpid());
   int answer = 0;
   for (int i = 0; i<size; i++){
       answer += array[i];
       array[i] += 10;
   }

   printf("Answer is %d\n", answer);
   return answer;

}

int main(){
    int forkReturnValue;

    int array[10] = {1,2,3,4,5,6,7,8,9,10};

    pid_t myPID = getpid();
    printf("The main process id is %d \n", myPID);

    forkReturnValue = fork();

    //error checking
    if (forkReturnValue < 0){
        perror("Failed to fork. \n");
        exit(1);
    }

    //child process
    if (forkReturnValue == 0){
        //child process will have forkReturnValue of 0
        child_process_function(array, 10,0);
    }
    else
    {
        //parent process will have forkReturnValue of > 0, which is the pid of the child
        //wait for a child (any 1)
        pid_t childPid = wait(NULL);
        printf("Child process has finished. Main process exiting\n");
    }

    printf("The address of the array in pid %d starts at %p \n", getpid(), array);
    printf("The value of the array in pid %d is : ", getpid());
    for(int i = 0; i<10 ;i++){
        printf(" %d ", array[i]);
    }
    printf("\n");
}