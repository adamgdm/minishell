/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:23:57 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/09 00:26:18 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	k;
	size_t	len_s;
	size_t	i;

	i = 0;
	len_s = ft_strlen(s);
	k = (char) c;
	while (i <= len_s)
	{
		if (s[len_s - i] == k)
			return ((char *)(s + len_s - i));
		i++;
	}
	return (0);
}
