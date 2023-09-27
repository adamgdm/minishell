#include "../minishell.h"

int isdnin(char *cmd, char *arraytofind)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!cmd)
        return (0);
    while (cmd[i])
    {
        if (cmd[i] == arraytofind[j])
        {
            j++;
            if(!arraytofind[j])
            {
                while (cmd[i] == 'n')
                    i++;
                if (!cmd[i])
                    return (1);
            }
        }
        else
            j = 0;
        i++;
    }
    return (0);
}

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
    while (isdnin(cmd[i], "-n"))
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
