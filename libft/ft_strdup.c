/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:59:04 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/18 23:05:49 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;
	size_t	j;

	j = 0;
	i = ft_strlen(s1);
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	while (s1[j])
	{
		s[j] = s1[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}
