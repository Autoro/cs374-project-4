#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
    char path[128];
    int pfd[2];
    pid_t pid;

    if (argc > 1)
    {
        strcpy(path, argv[1]);
    }
    else
    {
        strcpy(path, ".");
    }

    if(pipe(pfd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        dup2(pfd[0], 0);
        close(pfd[1]);
        
        execlp("wc", "wc", "-l", NULL);

        perror("execlp");
        exit(1);
    }

    dup2(pfd[1], 1);
    close(pfd[0]);

    execlp("ls", "ls", "-1a", path, NULL);

    perror("execlp");
    exit(1);
}
