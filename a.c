#include <unistd.h>

int main(int ac, char **av, char *envp[])
{
    (void)ac;
    (void)av;
		 char *afd[] = {"/bin/echo", "-n", "hello", NULL};
		 execve("/bin/echo", afd, envp);
}