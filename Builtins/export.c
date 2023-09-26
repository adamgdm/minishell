#include "../minishell.h"

int ft_iseqin(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void printenv(t_env *head, int fd) 
{
    t_env *current ;
    
    current = head;
    while (current) 
    {
        ft_putstr_fd("declare -x ", fd);
        ft_putstr_fd(current->str, fd);
        ft_putchar_fd('\n', fd);
        current = current->next;
    }
}

void    ft_export(t_env **env, t_env **envnocmd, t_commands *cmnd, int fd)
{
    t_env *head;
    int i;

    i = 1;
    head = (*envnocmd);
    if (!cmnd->cmd[i])    
        printenv(head, fd);
    else
    {
        while (cmnd->cmd[i])
        {
            if (ft_iseqin(cmnd->cmd[i]))
            {    
                add_before_last_node(env, cmnd->cmd[i]);            
                add_before_last_node(envnocmd,cmnd->cmd[i]);
            }
            else
                add_before_last_node(envnocmd,cmnd->cmd[i]);
            i++;
        }
    }
}