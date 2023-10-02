#include "../minishell.h"


int _process_env_value(char *value)
{
    int i;

    i = 0;
    if (ft_strlen(value) == 0)
        return (0);
    while (value[i] && (value[i] == ' ' || value[i] == '\t'))
        i++;
    while (value[i])
    {
        if (value[i] == ' ' || value[i] == '\t')
        {
            while (value[i] && (value[i] == ' ' || value[i] == '\t'))
                i++;
            if (!value[i])
                return (1);
            else
                return (0);
        }
        i++;
    }
    return (1);
}