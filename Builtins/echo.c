#include "../minishell.h"

void ft_echo_norm(char **cmd, int nl)
{
    int i;

    i = 1;
    while (cmd[i])
    {
            printf("%s", cmd[i]);
            if (cmd[i + 1])
                printf(" ");
        i++;
    }
    if (nl)
        printf("\n");
}

void    ft_echo(char **cmd)
{
    int i;
    int nl;

   // printf("exit_status = %d\n", g_exit_status);
    i = 1;
    nl = 1;
    if (!cmd[i])
    {
        printf("\n");
        g_exit_status = 0;
        return ;
    }
    while (ft_rulefinder(cmd[i], ft_strdup("-n")))
    {    
        nl = 0;
        i++;
    }
    if (!cmd[i])
    {
        g_exit_status = 0;
        return ;
    }
    ft_echo_norm(cmd, nl);
    g_exit_status = 0;
}
