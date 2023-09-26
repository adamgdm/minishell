/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:57:59 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/17 15:20:48 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	size_t	j;
	char	t;
	char	*p;

	t = (char) c;
	p = (char *) s;
	j = 0;
	len = ft_strlen(s) + 1;
	while (j < len)
	{
		if (p[j] == t)
			return (p + j);
		j++;
	}
	return (NULL);
}
