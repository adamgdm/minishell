#include "../minishell.h"

char    *ft_retpwd(void)
{
    char *buffer;
    char *ret;
    int i;

    i = pathconf(".", _PC_PATH_MAX);
    if (!i || i == -1)
    {
        perror("Pathconf: ");
        exit(1);
    }

    buffer = malloc(sizeof(char) * i);
    if (!buffer)
    {
        perror("Malloc: ");
        exit(1);
    }
    ret = getcwd(buffer, i);
    if (ret == NULL)
    {
        perror("Getcwd: ");
        free(buffer); 
        exit(1);
    }
    
    return buffer;
}

void    ft_pwd(int fd)
{
    char *buffer;
    int i;

    i = pathconf(".", _PC_PATH_MAX);
    if (!i || i == -1)
    {
        perror("Pathconf: ");
        exit(1);
    }
    buffer = malloc(sizeof(char) * i);
    if (!buffer)
    {
        perror("Malloc: ");
        free(buffer);
        exit(1);
    }
    buffer = getcwd(buffer, i);
    ft_putstr_fd(buffer, fd);
    ft_putchar_fd('\n', fd);
    free (buffer);
}