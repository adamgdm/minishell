#include "../minishell.h"


t_token *_lexer(char *input)
{
	t_token             *head;
	t_token             *current;
    int                 i;
    int                 j;
    char                *s;
    // char                *tmp;

    i = 0;
    j = 0;
    head = NULL;
    s = NULL;
    while(input[i]) {
        while(input[i] && (input[i] == ' ' || input[i] == '\t'))
            i++;
        if (!input[i])
            break;
        if (!_it_contains(input[i])) {
            j = i;
            while(input[i] && !_it_contains(input[i])) {
                if (input[i] == '\"') {
                    i++;
                    j = i;
                    while(input[i] && input[i] != '\"')
                        i++;
                    if (!input[i]) {
                        printf("Error: unclosed double quote\n");
                        g_exit_status = 258;
                        _free_all_tokens(&head, 1);
			            free(input);
                        return (NULL);
                    }
                else if (input[i] == '\"') {
                    if ((input[i+1] && _it_contains(input[i+1])) || !input[i+1])
                        current = _create_token(ft_substr(input, j, i - j), WORD, IN_DQUOTE, 1);
                    else
                        current = _create_token(ft_substr(input, j, i - j), WORD, IN_DQUOTE, 0);
                    _add_token(&head, current);
                    i++;
                    j = i;
                }
            
                }
                else if (input[i] == '\'') {
                    i++;
                    j = i;
                    while(input[i] && input[i] != '\'')
                        i++;
                    if (!input[i])
                    {
                        printf("Error: unclosed single quote\n");
                        g_exit_status = 258;
                        _free_all_tokens(&head, 1);
                        free(input);
                        return (NULL);
                    }
                    else if (input[i] == '\'') {
                        if ((input[i+1] && _it_contains(input[i+1])) || !input[i+1])
                            current = _create_token(ft_substr(input, j, i - j), WORD, IN_QUOTE, 1);
                        else
                            current = _create_token(ft_substr(input, j, i - j), WORD, IN_QUOTE, 0);
                        _add_token(&head, current);
                        i++;
                        j = i;
                    }
                }
                else {
                    s = _append(s, input[i]);
                    i++;
                    if (_it_contains(input[i]) || !input[i] || input[i] == '\"' || input[i] == '\'') {
                        if (input[i] == '"' || input[i] == '\'')
                            current = _create_token(s, WORD, GENERAL, 0);
                        else
                            current = _create_token(s, WORD, GENERAL, 1);
                        _add_token(&head, current);
                        s = NULL;
                    }
                }                      
            }


        }
        _token_creation(input, &head, &i);

}

return (head);
}