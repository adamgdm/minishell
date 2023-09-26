/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:08:22 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/17 15:22:21 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*d;

	d = (char *)haystack;
	i = 0;
	j = 0;
	if (!needle[i])
		return (d);
	while (i + j < len && d[i])
	{
		j = 0;
		while (needle[j] && d[i + j] == needle[j] && i + j < len)
		{
			if (!needle[j + 1])
				return (d + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
