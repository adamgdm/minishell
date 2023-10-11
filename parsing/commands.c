#include "../minishell.h"

t_commands  *_create_command(t_vars3 *vars)
{
    t_commands  *new;

    new = malloc(sizeof(t_commands));
    if (!new)
        return (NULL);
    new->cmd = vars->commands;
    new->in_file = vars->in_file;
    new->out_file = vars->out_file;
    new->pipefd = vars->result_pipe;
    new->error_exist = vars->error;
    new->pid = -1;
    new->next = NULL;
    new->previous = NULL;
    return (new);
}

void    _add_command(t_commands **head, t_commands *new)
{
    t_commands *current;

    if (!*head)
    {
        *head = new;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new;
    new->previous = current;

}