#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <cstring>
#include <unistd.h>

int main()
{
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if(shmid == -1)
    {
        std::cerr <<"Shared memory creation failed\n";
        return 1;
    }
    
    pid_t pid = fork();

    if(pid < 0)
    {
        std::cerr <<"fork() failed\n";
    }

    if(pid > 0) // parent process
    {
        // Attach SM
        char* str = (char*)shmat(shmid, (void*)0, 0);
        std::strcpy(str, "Hello from parent process\n");

        // Detach from SM
        shmdt(str);

        wait(NULL);

        // Destroy SM
        shmctl(shmid, IPC_RMID, NULL);
    }
    else // child process
    {
        char* str = (char*) shmat(shmid, (void*)0, 0);

        std::cout <<"Msg received: " << str << "\n";
        shmdt(str);
    }
}