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
    int         parenthesis;
    int         i;
    int         j;
    char*       tmp;

    current = *result;
    i = 0;
    if (current->type == PIPE)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (1);
    }
    
    while (current)
    {
        if (_check_type(current->type))
        {
            if (!current->next)
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                g_exit_status = 2;
                return (1);
            }
            if (_check_type(current->next->type) || current->next->type == PIPE)
            {
                printf("minishell: syntax error near unexpected token `%s'\n", current->next->content);
                g_exit_status = 2;
                return (1);
            }
        }
        if (current->type == PIPE)
        {
            if (!current->next || current->next->type == PIPE)
            {
                printf("minishell: syntax error near unexpected token `|'\n");
                g_exit_status = 2;
                return (1);
            }
        }
        // handling echo (ok) -> syntax error near unexpected token `ok'
        if (current->type == WORD && ft_strchr(current->content, ')')
            && !ft_strchr(current->content, '(') && !ft_strchr(current->content, '\\'))
        {
            printf("minishell: syntax error near unexpected token `)'\n");
            g_exit_status = 2;
            return (1);
        }
        if (current->type == WORD && (ft_strchr(current->content, ')')
            || ft_strchr(current->content, '(')) && !ft_strchr(current->content, '\\'))
        {
            while (current->content[i])
            {
                if (current->content[0] == '(')
                {
                    i++;
                    j = i;
                    while (current->content[i] && current->content[i] != ')' && current->content[i] != '('
                        && current->content[i] != ' ')
                        i++;
                    tmp = ft_substr(current->content, j, i - j);
                    printf("minishell: syntax error near unexpected token `%s'\n", tmp);
                    free(tmp);
                    g_exit_status = 2;
                    return (1);
                    
                }
                if (current->content[0] == ')')
                {
                    printf("minishell: syntax error near unexpected token `)'\n");
                    g_exit_status = 2;
                    return (1);
                }
                if (current->content[i] == '(')
                {
                    printf("minishell: syntax error near unexpected token `('\n");
                    g_exit_status = 2;
                    return (1);
                }
                i++;

            }
        }
        
        current = current->next;
    }
    return (_here_doc_counter(result));

} 