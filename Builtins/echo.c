#include "../minishell.h"

void    ft_echo(char **cmd)
{
    int i;
    int nl;

    i = 1;
    nl = 1;
    printf("%p\n", cmd[0]);
    if (!cmd[i])
    {
        printf("\n");
        return ;
    }
    while (ft_rulefinder(cmd[i], ft_strdup("-n")))
    {    
        nl = 0;
        i++;
    }
    if (!cmd[i])
        return ;
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
