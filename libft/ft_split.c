/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:33:22 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/14 11:25:41 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct helper {
	char	**p;
	char	**t;
	char	**h;
	size_t	i;
	size_t	counter;
	size_t	counter2;
	size_t	k;
	size_t	len;
	size_t	j;
	size_t	s;
}	t_H;

static char	**free_error(char **p, size_t j)
{
	size_t	k;

	k = 0;
	while (k < j)
		free(p[k]);
	free(p);
	return (NULL);
}

static char	**ftmalloc(char **p, size_t n, char const *s, char c)
{
	t_H		x;
	size_t	i;

	x.len = ft_strlen(s);
	i = 0;
	x.j = 0;
	x.k = 0;
	x.counter2 = 0;
	while (i < x.len && x.j < n)
	{
		x.counter2 = 0;
		while (s[i] == c && i < x.len)
			i++;
		while (s[i] != c && i < x.len)
		{
			x.counter2++;
			i++;
		}
		p[x.j] = malloc(x.counter2 + 1);
		if (!p[x.j])
			return (free_error(p, x.j));
		x.j++;
	}
	return (p);
}

static char	**ftcpy(char **p, size_t n, char const *s, char c)
{
	t_H	z;

	z.len = ft_strlen(s);
	z.j = 0;
	z.s = 0;
	z.i = 0;
	while (z.i < z.len && z.j < n)
	{
		z.s = 0;
		while (s[z.i] == c && z.i < z.len)
			z.i++;
		while (s[z.i] != c && z.i < z.len)
		{
			p[z.j][z.s] = s[z.i];
			z.s++;
			z.i++;
		}
		p[z.j][z.s] = '\0';
		z.j++;
	}
	p[z.j] = NULL;
	return (p);
}

static char	**null_check(char **p)
{
	p = malloc(sizeof(char *));
	if (!p)
		return (NULL);
	p[0] = (NULL);
	return (p);
}

char	**ft_split(char const *s, char c)
{
	t_H	g;

	g.counter = 0;
	g.p = NULL;
	g.i = 0;
	if (!s)
		return (NULL);
	g.len = ft_strlen(s);
	while (g.i < g.len)
	{
		if (s[g.i] != c && (s[g.i + 1] == c || !s[g.i + 1]))
			g.counter++;
		g.i++;
	}
	if (!g.counter)
		return (null_check(g.p));
	g.p = malloc((g.counter + 1) * sizeof (char *));
	if (!g.p)
		return (NULL);
	g.t = ftmalloc(g.p, g.counter, s, c);
	g.h = ftcpy(g.t, g.counter, s, c);
	return (g.h);
}
