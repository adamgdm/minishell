/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:26:33 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/09 18:12:57 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_forward(char const *s1, char const *set)
{
	size_t	k;
	size_t	j;
	size_t	len;
	size_t	i;

	k = 0;
	j = ft_strlen(set);
	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		k = 0;
		while (k < j)
		{
			if (s1[i] == set[k])
				break ;
			k++;
		}
		if (k == j)
			break ;
		i++;
	}
	return (i);
}

static size_t	check_backward(char const *s1, char const *set)
{
	size_t	k;
	size_t	j;
	int		len;

	k = 0;
	j = ft_strlen(set);
	len = ft_strlen(s1);
	while (len >= 0)
	{
		k = 0;
		while (k < j)
		{
			if (s1[len - 1] == set[k])
				break ;
			k++;
		}
		if (k == j)
			break ;
	len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			i;
	size_t			len;
	char			*p;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (!set)
		return (ft_strdup(s1));
	if (!ft_strlen(s1))
		return (ft_strdup(""));
	i = check_forward(s1, set);
	if (i == len)
		return (ft_strdup(""));
	len = check_backward(s1, set);
	p = ft_substr(s1, i, (len - 1) - i + 1);
	if (!p)
		return (NULL);
	return (p);
}
