#include "cclass.h"

int main(){
    
    //1. allocate shared memory, get its id
    int ShmID = shmget(IPC_PRIVATE, sizeof(Vec2D), S_IRUSR | S_IWUSR);

    //2. attach to this process’ address space
    Vec2D* ShmPTR = (Vec2D *)shmat(ShmID, NULL, 0); // get Vec2D from the Thread part, same struct used
    
    //init to zero
    ShmPTR->x = 0;
    ShmPTR->y = 0;

    int pid = fork();
    if (pid < 0)
    {
        printf("*** fork error (server) ***\n");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("From pid %d, x and y value is (%d, %d) \n", getpid(), ShmPTR->x, ShmPTR->y);
        //sleep, hoping parent will finish by then
        sleep(5);
        printf("From pid %d, new x and y value is (%d, %d) \n", getpid(), ShmPTR->x,ShmPTR->y);
        //child change the  shared memory value
        ShmPTR->x = 5;
        ShmPTR->y = 5;
        exit(0); //child exits
    }

    //sleep, hoping child will finish printing by then
    sleep(1);
    //parent code
    ShmPTR->x = 10;
    ShmPTR->y = 10;
    wait(NULL); //wait for child
    printf("From pid %d, new x and y value is (%d, %d) \n", getpid(), ShmPTR->x, ShmPTR->y);

    //3. detach shared memory
    shmdt((void *)ShmPTR);
    //4. delete shared memory
    shmctl(ShmID, IPC_RMID, NULL);

}