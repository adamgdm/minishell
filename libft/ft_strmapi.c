/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:02:31 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/17 03:04:24 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*t;
	char	*p;

	i = 0;
	if (!s || !f)
		return (NULL);
	t = (char *)s;
	p = malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (t[i])
	{
		p[i] = t[i];
		i++;
	}
	p[i] = '\0';
	i = 0;
	while (t[i])
	{
		p[i] = f(i, t[i]);
		i++;
	}
	return (p);
}
