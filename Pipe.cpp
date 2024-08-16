#include <iostream>
#include <unistd.h> // for pipe(), fork(), read(), write()
#include <cstring>
#include <sys/wait.h>

int main()
{
    int pipe_fds[2]; // array to hold 2 ends of pipe
    pid_t pid;

    const char* msg = "Hello from parent process\n";
    char buff[128];

    // create pipe
    if(pipe(pipe_fds) == -1)
    {
        std::cerr <<"Pipe creation failed\n";
        return 1;
    }

    // Fork the process
    pid = fork();

    if(pid < 0) 
    {
        std::cerr <<"fork() failed\n";
        return 1;
    }

    if(pid > 0) // parent process
    {
        close(pipe_fds[0]); // Close the read end of pipe

        // write message to pipe
        write(pipe_fds[1], msg, strlen(msg)+1);
        close(pipe_fds[1]); // close write end of pipe after msg is written
        wait(NULL);
    }
    else // child process
    {
        close(pipe_fds[1]);

        read(pipe_fds[0], buff, sizeof(buff));
        close(pipe_fds[0]);

        std::cout <<"child received msg: " << buff <<"\n";
    }

    return 0;
}