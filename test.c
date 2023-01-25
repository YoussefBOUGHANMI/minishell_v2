#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
		char *args[] = {"lo", NULL};
		
		if(execve("/bin/lo", args, NULL) == -1)
			printf("erreur\n");
    } else {
        close(fd[1]);
        wait(NULL);
        char buffer[1024];
        int n = read(fd[0], buffer, sizeof(buffer));
        buffer[n] = '\0';
       printf("Output: %s\n", buffer);
    }
    return 0;
}