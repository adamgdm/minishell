/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:42:32 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/14 11:25:31 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if (!count || !size)
	{
		p = malloc(0);
		if (!p)
			return (NULL);
		return (p);
	}
	if (size > SIZE_MAX / count && count != 0)
		return (0);
	p = malloc(size * count);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
