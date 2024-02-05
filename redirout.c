#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <outfilename> <command> <opt1> <opt2> ...\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    if (dup2(fd, 1) == -1)
    {
        perror("dup2");
        exit(1);
    }

    execvp(argv[2], argv + 2);
    perror("execvp");
    exit(1);
}
