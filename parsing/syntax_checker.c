#include "../minishell.h"


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
                return (1);
            }
            if (_check_type(current->next->type) || current->next->type == PIPE)
            {
                printf("minishell: syntax error near unexpected token `%s'\n", current->next->content);
                return (1);
            }
        }
        if (current->type == PIPE)
        {
            if (!current->next)
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return (1);
            }
            if (current->next->type == PIPE)
            {
                printf("minishell: syntax error near unexpected token `|'\n");
                return (1);
            }
        }
        // handling echo (ok) -> syntax error near unexpected token `ok'
        if (current->type == WORD && ft_strchr(current->content, ')')
            && !ft_strchr(current->content, '(') && !ft_strchr(current->content, '\\'))
        {
            printf("minishell: syntax error near unexpected token `)'\n");
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
                    printf("minishell: sytax error near unexpected token `%s'\n", tmp);
                    free(tmp);
                    return (1);
                    
                }
                if (current->content[i] == '(')
                {
                    printf("minishell: syntax error near unexpected token `('\n");
                    return (1);
                }
                if (current->content[i] == ')' && parenthesis == 0)
                {
                    printf("minishell: syntax error near unexpected token `)'\n");
                    return (1);
                }
                i++;

            }
        }
        
        current = current->next;
    }
    return (0);

} 