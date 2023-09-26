/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:19:35 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/14 08:58:33 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (0);
	if (!s[i] && !d[i])
		return (d);
	if (dst > src)
	{
		while (len > 0)
		{
			*(d + len - 1) = *(s + len - 1);
			len--;
		}
	}
	else
		return (ft_memcpy(dst, src, len));
	return (d);
}
