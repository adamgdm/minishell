/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:05:28 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/12 01:18:14 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	_write_to_pipe(char *content, int check, t_data *data, int *fd)
{
	char	*s;

	while (1)
	{
		s = readline(">");
		if (!s)
			break ;
		if (!_strcmp(s, content))
		{
			free(s);
			break ;
		}
		if (check == 1)
			s = _expand_word(s, data);
		write(fd[1], s, ft_strlen(s));
		write(fd[1], "\n", 1);
		free(s);
	}
}

int	*_here_doc(char *content, int check, t_data *data)
{
	pid_t	pid;
	int		*fd;

	fd = malloc(sizeof(int) * 2);
	pipe(fd);
	pid = fork();
	signal(SIGINT, ft_sigints);
	if (pid == 0)
	{
		_write_to_pipe(content, check, data, fd);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(fd[1]);
		wait(NULL);
		return (fd);
	}
}
