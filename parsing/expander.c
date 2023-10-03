#include "../minishell.h"

int _contains_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return 1;
        i++;
    }
    return 0;
}

char *_expand_word(char *content)
{
    char *result;
    char *tmp;
    char *tmp2;
    char *tmp3;
    char *save;
    int i;
    int j;
    int k;
    int on_off;

    i = 0;
    j = 0;
    k = 0;
    on_off = 0;
    save = ft_strdup("");
    while (content[i])
    {
        if (content[i] == '$') // $?fs
        {
            i++;
            k = i;
            on_off = 0;
            while (content[i] && !ft_strchr("+*-?<>{}[]^()#%@\"'$&|;,/\t ", content[i]))
                i++;
            if (k == i && content[i] == '?')
            {
                //printf("g_exit_status: %s\n", ft_itoa(g_exit_status));
                tmp3 = save;
                tmp = ft_itoa(g_exit_status);
                save = ft_strjoin(save, tmp);
                free(tmp3);
                free(tmp);
                i++;
                j = i;
                continue;
            }
            if (i == k)
            {
                if (!content[i])
                    save = _append(save, '$');
                else
                {
                    save = _append(save, '$');
                    save = _append(save, content[i]);
                    i++;
                }
                j = i;
                continue;
            }
            tmp = ft_substr(content, j + 1, i - j - 1);
            tmp2 = getenv(tmp);
            if (!tmp2)
                tmp2 = "";
            tmp3 = save;
            save = ft_strjoin(save, tmp2);
            free(tmp);
            free(tmp3);
            j = i;
        }
        if (content[i] && content[i] != '$')
        {

            save = _append(save, content[i]);
            i++;
            j = i;
        }
    }
    free(content);
    return save;
}

void _expander(t_token **result)
{
    t_token *head;

    head = *result;
    while (head)
    {
        if (head->type == HERE_DOC)
        {
            head = head->next->next;
            while (head && head->space_check == 0)
            {
                head = head->next;
            }
            if (head && head->type != HERE_DOC)
                head = head->next;
            continue;
        }
        if (_contains_dollar(head->content) && (head->state == GENERAL || head->state == IN_DQUOTE))
        {
            if (ft_strlen(head->content) != 1) {                ////////
                free(head->before_expanded);
                head->before_expanded = ft_strdup(head->content);// save the original content
            }
            head->content = _expand_word(head->content);
        }
        head = head->next;
    }
}