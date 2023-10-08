#include "../minishell.h"

static int	_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
    if (ft_strlen(s1) != ft_strlen(s2))
        return (1);
	while (a[i] || b[i])
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}



int *_here_doc(char *content, int check, t_data *data)
{
    pid_t pid;

    int *fd = malloc(sizeof(int) * 2);
    char *s;
    pipe(fd);
    pid = fork();
    signal(SIGINT, ft_sigint);
    if (pid == 0)
    {
        //close(fd[0]);
        while (1)
        {
            s = readline(">");
            if (!s)
                break;
            printf("%p\n", s);
            if (!_strcmp(s, content))
                break;
            if (check == 1)
                s = _expand_word(s, data);
            write(fd[1], s, ft_strlen(s));
            write(fd[1], "\n", 1);
            free(s);
        }
        exit(0);
       // close(fd[1]);
    }
    else
    {
        close(fd[1]);
        wait(NULL);
       // close(fd[0]);
        return (fd);
    }
}


