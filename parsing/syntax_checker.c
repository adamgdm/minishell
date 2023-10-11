#include "../minishell.h"

int _here_doc_counter(t_token** result)
{
    t_token*    current;
    int         counter;

    current = *result;
    counter = 0;
    while (current)
    {
        if (current->type == HERE_DOC)
            counter++;
        current = current->next;
    }
    if (counter > 16)
    {
        printf("minishell: maximum here-document count exceeded\n");
        g_exit_status = 2;
        return (-1);
    }
    return (0);
}

int _check_type(enum e_token type)
{
    if (type == REDIRECT_IN || type == REDIRECT_OUT || type == REDIRECT_APPEND || type == HERE_DOC) 
        return (1);
    return (0);
}


int _syntax_check(t_token** result)
{
    t_token*    current;

    current = *result;
    if (current->type == PIPE)
        return (_syntax_norm6());
    while (current)
    {
        if (_check_type(current->type) || current->type == PIPE)
        {
            if (_syntax_norm4(current))
                return (1);
        }
        if (current->type == WORD && ft_strchr(current->content, ')')
            && !ft_strchr(current->content, '(') && !ft_strchr(current->content, '\\'))
            return (_syntax_norm5());
        if (current->type == WORD && (ft_strchr(current->content, ')')
            || ft_strchr(current->content, '(')) && !ft_strchr(current->content, '\\'))
        {
            if (_syntax_norm3(current))
                return (1);
        } 
        current = current->next;
    }
    return (_here_doc_counter(result));
} 