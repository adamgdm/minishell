/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:16:18 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/08 22:17:30 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	f;
	size_t			i;

	i = 0;
	f = (unsigned char)c;
	d = (unsigned char *)s;
	while (i < n)
	{
		if (d[i] == f)
			return (d + i);
		i++;
	}
	return (NULL);
}
