#include "../minishell.h"

void    ft_echo(char **cmd, int fd)
{
    int i;
    int nl;

    i = 1;
    nl = 1;
    if (!cmd[i])
    {
        ft_putchar_fd('\n',fd);
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
            ft_putstr_fd(cmd[i],fd);
            if (cmd[i + 1])
                ft_putchar_fd(' ', fd);
        i++;
    }
    if (nl)
        ft_putchar_fd('\n',fd);
}
