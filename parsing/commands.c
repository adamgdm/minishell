#include "../minishell.h"

t_commands  *_create_command(char **commands, int in_file, int out_file, int *pipe, int error)
{
    t_commands  *new;

    new = malloc(sizeof(t_commands));
    if (!new)
        return (NULL);
    new->cmd = commands;
    new->in_file = in_file;
    new->out_file = out_file;
    new->pipefd = pipe;
    // printf("pipe_ne[0]: %d\n", new->pipefd[0]);
    // printf("pipe_ne[1]: %d\n", new->pipefd[1]);
    new->error_exist = error;
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