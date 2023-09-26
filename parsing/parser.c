#include "../minishell.h"


char    **_append_string(char **commands, char *content)
{
    int     i;
    char    **new;

    i = 0;
    while (commands && commands[i])
        i++;
    new = malloc(sizeof(char *) * (i + 2));
    if (!new)
        return (NULL);
    i = 0;
    while (commands && commands[i])
    {
        new[i] = commands[i];
        i++;
    }
    new[i] = content;
    new[i + 1] = NULL;
    if (commands)
        free(commands);
    return (new);
}

void   _print_array(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        printf("array[%d]: %s\n", i, array[i]);
        i++;
    }
}


t_commands  *_parser(t_token **result)
{
    char        **commands;
    int         in_file;
    int         out_file;
    t_token     *current;
    t_commands  *head;
    t_commands  *new;

    commands = NULL;
    in_file = 0;
    out_file = 1;
    current = *result;
    head = NULL;
    while (current)
    {
        if (current->type == WORD)
        {
            commands = _append_string(commands, current->content);
            //_print_array(commands);
        }
        if (current->type == REDIRECT_OUT)
        {
            if (out_file > 2)
                close(out_file);
            out_file = open(current->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_file == -1)
            {
                printf("minishell: %s: %s\n", current->next->content, strerror(errno));
                return (NULL);
            }
            current = current->next;
        }
        if (current->type == REDIRECT_APPEND)
        {
            if (out_file > 2)
                close(out_file);
            out_file = open(current->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (out_file == -1)
            {
                printf("minishell: %s: %s\n", current->next->content, strerror(errno));
                return (NULL);
            }
            current = current->next;
        }
        if (current->type == REDIRECT_IN)
        {
            if (in_file > 2)
                close(in_file);
            in_file = open(current->next->content, O_RDONLY);
            if (in_file == -1)
            {
                printf("minishell: %s: %s\n", current->next->content, strerror(errno));
                return (NULL);
            }
            current = current->next;
        }
        if (current->type == HERE_DOC)
        {
            current = current->next;
            // if (current->state ==  QUOTED || current->state == IN_QUOTE || current->state == IN_DQUOTE)
            //     _herdoc(head,current->next->content, 0, env);  // case : cat << ma'ma' || cat << "ma'ma" || cat << 'mama' || cat << "mama" the env is not expanded
            // else
            //     _herdoc(head,current->next->content, 1, env);  // case : cat << mama || cat << $mama || cat << ${mama} the env is expanded
        }
        if (current->type == PIPE)
        {
            new = _create_command(commands, in_file, out_file);
            _add_command(&head, new);
            commands = NULL;
            
        }
        current = current->next;
    }
    new = _create_command(commands, in_file, out_file);
    _add_command(&head, new);
    return (head);

}