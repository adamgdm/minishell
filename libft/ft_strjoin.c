/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:01:46 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/09 00:51:16 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct all {
	size_t	i;
	size_t	v;
	size_t	y;
	size_t	j;
	char	*p;
	char	*r;
	char	*s;
}	t_B;

char	*ft_strjoin(char *s1, char *s2)
{
	t_B	u;

	if(!s1 || !s2)
		return (NULL);
	u.v = 0;
	u.y = 0;
	u.i = ft_strlen(s1);
	u.j = ft_strlen(s2);
	u.p = malloc((u.i + u.j + 1) * sizeof(char));
	if (!u.p)
		return (NULL);
	u.r = ft_memcpy(u.p, s1, u.i);
	u.s = ft_memcpy(u.r + u.i, s2, u.j + 1);
	return (u.r);
}
