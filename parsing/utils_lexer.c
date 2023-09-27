#include "../minishell.h"

int _it_contains(int c)
{
    if (c == '|' || c == '<' || c == '>'
        || c == '\t' || c == ' ')
        return (1);
    return (0);
}

// function to add character to string

char *_append(char *str, char c)
{
    char *result;
    int i;

    i = 0;
    result = malloc(sizeof(char) * (ft_strlen(str) + 2));
    if (!result)
        return (NULL);
    while (str && str[i])
    {
        result[i] = str[i];
        i++;
    }
    result[i] = c;
    result[i + 1] = '\0';
    free(str);
    return (result);
}