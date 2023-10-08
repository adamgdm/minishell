#include "../minishell.h"

char *ft_returnpwd()
{
    char *buffer;
    int i;

    i = pathconf(".", _PC_PATH_MAX);
    if (!i || i == -1)
    {
        perror("Pathconf: ");
        g_exit_status = 1;
        exit(1);
    }
    buffer = malloc(sizeof(char) * i);
    if (!buffer)
    {
        perror("Malloc: ");
        free(buffer);
        g_exit_status = 1;
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
        g_exit_status = 1;
        exit(1);
    }
    buffer = malloc(sizeof(char) * i);
    if (!buffer)
    {
        perror("Malloc: ");
        free(buffer);
        g_exit_status = 1;
        exit(1);
    }
    buffer = getcwd(buffer, i);
    g_exit_status = 0;
    ft_putstr_fd(buffer, fd);
    ft_putchar_fd('\n', fd);
    free (buffer);
}