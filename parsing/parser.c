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
    char **commands;
    int in_file;
    int out_file;
    int error;
    t_token *current;
    t_commands *head;
    t_commands *new;
    int *fd;
    int p[2];
    int *result_pipe = malloc(sizeof(int) * 2);
    result_pipe[0] = -1;
    result_pipe[1] = -1;
    int previous_pipe = -1;
    int already_printed = 0;
    commands = NULL;
    in_file = 0;
    out_file = 1;
    error = 0;
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
            if (out_file == -1 && !already_printed)
            {
                if (ft_strlen(current->next->before_expanded) != 0 && ft_strlen(current->next->content) == 0)
                {
                    printf("minishell: %s: ambiguous redirect\n", current->next->before_expanded);
                }
                else
                    printf("minishell: %s: %s\n", current->next->content, strerror(errno));
                error = 1;
                already_printed = 1;
            }
            free(current->content);
            current->content = NULL;
            current = current->next;
            free(current->content);
            current->content = NULL;
        }
        if (current->type == REDIRECT_APPEND)
        {
            if (out_file > 2)
                close(out_file);
            out_file = open(current->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (out_file == -1 && !already_printed)
            {
                printf("minishell: %s: %s\n", current->next->content, strerror(errno));
                error = 1;
                already_printed = 1;
            }
            free(current->content);
            current->content = NULL;
            current = current->next;
            free(current->content);
            current->content = NULL;
        }
        if (current->type == REDIRECT_IN)
        {
            if (in_file > 2)
                close(in_file);
            in_file = open(current->next->content, O_RDONLY);
            if (in_file == -1 && !already_printed)
            {
                if (ft_strlen(current->next->before_expanded) != 0)
                {
                    if (ft_strlen(current->next->content) == 0 || _is_there_space_or_tab(current->next->content) == 1)
                        printf("minishell: %s: ambiguous redirect\n", current->next->before_expanded);
                    else
                        printf("minishell: %s: No such file or directory\n", current->next->content);
                }
                else
                    printf("minishell: %s: %s\n", current->next->content, strerror(errno));
                error = 1;
                already_printed = 1;
                // return (NULL);
            }
            free(current->content);
            current->content = NULL;
            current = current->next;
            free(current->content);
            current->content = NULL;
        }
        if (current->type == HERE_DOC)
        {
            if (current->next->state == GENERAL)
                fd = _here_doc(current->next->content, 1, data); // case : cat << ma'ma' || cat << "ma'ma" || cat << 'mama' || cat << "mama" the env is not expanded
            else
                fd = _here_doc(current->next->content, 0, data); // case : cat << mama || cat << $mama || cat << ${mama} the env is expanded

            in_file = fd[0];
            free(fd);
            free(current->content);
            current->content = NULL;
            current = current->next;
            free(current->content);
            current->content = NULL;
        }
        if (current->type == PIPE)
        {

            result_pipe[0] = previous_pipe;
            pipe(p);
            result_pipe[1] = p[1];
            previous_pipe = p[0];

            // printf("pipefd[0]: %d\n", result_pipe[0]);
            // printf("pipefd[1]: %d\n", result_pipe[1]);

            new = _create_command(commands, in_file, out_file, result_pipe, error);
            _add_command(&head, new);
            commands = NULL;
            error = 0;
            free(current->content);
            current->content = NULL;
            // free(result_pipe);
            result_pipe = malloc(sizeof(int) * 2);
            // printf("%p\n", result_pipe);
            result_pipe[0] = -1;
            result_pipe[1] = -1;
            already_printed = 0;
        }

        current = current->next;
    }
    result_pipe[0] = previous_pipe;
    result_pipe[1] = -1;
    // printf("last pipefd[0]: %d\n", result_pipe[0]);
    // printf("last pipefd[1]: %d\n", result_pipe[1]);
    new = _create_command(commands, in_file, out_file, result_pipe, error);
    _add_command(&head, new);
    return (head);
}