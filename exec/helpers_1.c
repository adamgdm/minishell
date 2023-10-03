#include "../minishell.h"

t_env *createEnvNode(char *str) 
{
    t_env *newNode = (t_env *)malloc(sizeof(t_env));
    if (newNode) {
        newNode->str = ft_strdup(str);
        newNode->next = NULL;
    }
    return newNode;
}

void appendEnvNode(t_env **head, char *str) {
    t_env *newNode = createEnvNode(str);
    if (!newNode) {
        perror("malloc");
        exit(1);
    }

    if (*head == NULL) {
        *head = newNode;
    } else {
        t_env *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

t_env *charArrayToEnvList(char **charArray) {
    t_env *head = NULL;
    int i;

    i = 0;
    while (charArray[i]) 
    {
        appendEnvNode(&head, charArray[i]);
        i++;
    }
    return head;
}

int ft_rulefinder(char *cmd, char *arraytofind)
{
    int i = 0;
    int j = 0;

    /*printf("1: \'%s\'\n", cmd);
    printf("2: \'%s\'\n", arraytofind);*/
    
    if (!arraytofind)
        return (0);
    if (!cmd)
    {    
        free(arraytofind);
        return (0);
    }
    while (cmd[i])
    {
        if (i && !arraytofind[i])
        {    
            free(arraytofind);
            return (1);
        }
        if (cmd[i] != arraytofind[i])
        {    
            free(arraytofind);
            return (0);
        }
        i++;
    }
    if (arraytofind[i] == '\0')
        j = 1;
    free(arraytofind);
    return j; // Strings do not match at every character position
}

char *getValue(char *input) 
{
    char *equalsPtr;
    int substringLength;
    char *substring;

    equalsPtr = ft_strchr(input, '=');
    if (!equalsPtr)
    {
        return NULL;
    }
    substringLength = ft_strlen(equalsPtr + 1);
    substring = (char *)malloc(substringLength + 1);
    if(!substring)
    {
        perror("malloc");
        exit(1);
    }
    ft_strcpy(substring, equalsPtr + 1);
    return substring;
}



char *fetchValue(char *str, t_env *head)
{
    t_env *cur;
    char *strr;

    cur = head;
    int i = 0;
    while (cur)
    {
        if (ft_rulefinder(cur->str, ft_strjoin(str, "=")))
            break ;
        cur = cur->next;
        i++;
    }
    if (!cur)
        return (NULL);
    strr = getValue(cur->str);
    return (strr);
}

char* ft_strcpy(char* dest, const char* src) 
{
    int i;
    
    i = 0;
    while (src[i] != '\0') 
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}