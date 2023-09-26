/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:40:21 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/14 03:51:39 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct helper2 {
	size_t	i;
	char	*p;
	size_t	j;
	size_t	lens;
	size_t	start2;
}	t_ok;

static char	*helper(unsigned int start, size_t lens, char const *s)
{
	char			*q;
	size_t			start2;
	size_t			j;
	size_t			counter;

	start2 = start;
	j = 0;
	while (start < lens)
		start++;
	start--;
	q = malloc(start - start2 + 1 + 1);
	if (!q)
		return (NULL);
	counter = start - start2 + 1;
	while (j < counter)
	{
		q[j] = s[start2];
		j++;
		start2++;
	}
	q[j] = '\0';
	return (q);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	t_ok	v;

	if (!s)
		return (NULL);
	v.i = start;
	v.j = 0;
	v.lens = ft_strlen(s);
	if (!v.lens || !len)
		return (ft_strdup(""));
	if (start + len >= v.lens + 1)
		return (helper(start, v.lens, s));
	v.p = malloc(len + 1);
	if (!v.p)
		return (NULL);
	while (v.i < v.lens && v.j < len)
	{
		v.p[v.j] = s[v.i];
		v.j++;
		v.i++;
	}
	v.p[v.j] = '\0';
	return (v.p);
}
