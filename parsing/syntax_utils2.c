#include "../minishell.h"

int _syntax_norm5(void)
{
    printf("minishell: syntax error near unexpected token `)'\n");
    g_exit_status = 258;
    return (1);
}

int _syntax_norm6(void)
{
    printf("minishell: syntax error near unexpected token `|'\n");
    g_exit_status = 258;
    return (1);
}

int _syntax_norm7(t_token *current, int i)
{
    int j;
    char *tmp;

    i++;
    j = i;
    while (current->content[i] && current->content[i] != ')' && current->content[i] != '(' && current->content[i] != ' ')
        i++;
    tmp = ft_substr(current->content, j, i - j);
    printf("minishell: syntax error near unexpected token `%s'\n", tmp);
    free(tmp);
    g_exit_status = 258;
    return (1);
}

void _update_tokens_utils(t_token *current)
{
    char *s;
    t_token *tmp;

    s = current->content;
    current->content = ft_strjoin(current->content, current->next->content);
    free(s);
    current->before_expanded = _append(current->before_expanded, ' ');
    s = current->before_expanded;
    current->before_expanded = ft_strjoin(current->before_expanded, current->next->before_expanded);
    free(s);
    if (current->state + current->next->state != 0)
        current->state = QUOTED;
    tmp = current->next;
    if (current->next && current->next->space_check == 1)
        current->space_check = 1;
    current->next = current->next->next;
    free(tmp->content);
    free(tmp->before_expanded);
    free(tmp);
}