#include "../minishell.h"

char **_append_string(char **commands, char *content)
{
    int i; ////////////// check here;
    char **new;

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

void _print_array(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        printf("array[%d]: %s\n", i, array[i]);
        i++;
    }
}

int _is_there_space_or_tab(char *content)
{
    int i;
    i = 0;
    while (content[i])
    {
        if (content[i] == ' ' || content[i] == '\t')
            return (1);
        i++;
    }
    return (0);
}

t_commands *_parser(t_token **result, t_data *data)
{
    t_vars3 vars;

    t_token *current;
    t_commands *head;
    t_commands *new;
    int p[2];
    vars.result_pipe = malloc(sizeof(int) * 2);
    vars.result_pipe[0] = -1;
    vars.result_pipe[1] = -1;
    vars.previous_pipe = -1;
    vars.commands = NULL;
    vars.in_file = 0;
    vars.out_file = 1;
    vars.error = 0;
    vars.already_printed = 0;
    current = *result;
    head = NULL;
    while (current)
    {
        if (current->type == WORD)
            vars.commands = _append_string(vars.commands, current->content);
        if (current->type == REDIRECT_OUT)
        {
            _parser_norm(current, &vars.out_file, &vars.error, &vars.already_printed);
            _parser_free_norm(current);
        }
        if (current->type == REDIRECT_APPEND)
        {
            _parser_norm2(current, &vars.out_file, &vars.error, &vars.already_printed);
            _parser_free_norm(current);
        }
        if (current->type == REDIRECT_IN)
        {
            _parser_norm3(current, &vars.in_file, &vars.error, &vars.already_printed);
            _parser_free_norm(current);
        }
        if (current->type == HERE_DOC)
        {
            _parser_norm4(current, &vars.in_file, data);
            _parser_free_norm(current);
        }
        if (current->type == PIPE)
        {
            _parser_norm5(&head, &vars.result_pipe, &vars, &vars.previous_pipe);
            free(current->content);
            current->content = NULL;
        }

        current = current->next;
    }
    vars.result_pipe[0] = vars.previous_pipe;
    vars.result_pipe[1] = -1;
    new = _create_command(&vars);
    _add_command(&head, new);
    return (head);
}