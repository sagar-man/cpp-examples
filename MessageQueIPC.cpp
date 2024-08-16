#include <iostream>
#include <sys/ipc.h> // ftok()
#include <sys/msg.h>
#include <cstring>
#include <sys/wait.h> // wait()
#include <unistd.h>

struct msg_buff
{
    long msg_type;
    char msg_text[1024];
};

int main()
{
    key_t key;
    int msgid;

    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

    if(msgid == -1)
    {
        std::cerr <<"Msg que creation failed\n";
        return 1;
    }
    
    pid_t pid = fork();

    if(pid < 0)
    {
        std::cerr <<"fork() failed\n";
        return 1;
    }

    if(pid > 0) // parent process
    {
        msg_buff msg;
        msg.msg_type=1;
        std::strcpy(msg.msg_text, "Hello from parent process");

        auto ret = msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
        if(ret == -1)
        {
            std::cerr << "msg send failed\n";
            return 1;
        }

        wait(NULL);

        // destory msg queue
        msgctl(msgid, IPC_RMID, NULL);
    }
    else // child process
    {
        msg_buff msg;

        auto ret = msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
        if(ret == -1)
        {
            std::cerr << "msg receive failec\n";
        }

        std::cout <<"Child process received msg: " << msg.msg_text <<"\n";
    }

    return 0;

}
