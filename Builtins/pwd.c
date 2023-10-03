#include "../minishell.h"

char *ft_returnpwd()
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
    return (buffer);
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