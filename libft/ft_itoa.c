/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:01:09 by afaqir            #+#    #+#             */
/*   Updated: 2022/11/08 22:07:48 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkdigit(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

static char	*print_pos(int n, int d)
{
	char	*s;

	s = malloc(d + 1);
	if (!s)
		return (NULL);
	s[d] = '\0';
	d--;
	while (d >= 0)
	{
		s[d] = n % 10 + 48;
		n /= 10;
		d--;
	}
	return (s);
}

static char	*print_neg(int n, int d)
{
	char	*s;
	long	g;

	g = n;
	s = malloc(d + 2);
	if (!s)
		return (NULL);
	s[d + 1] = '\0';
	while (d >= 1)
	{
		s[d] = -g % 10 + 48;
		g /= 10;
		d--;
	}
	s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	int		d;

	d = checkdigit(n);
	if (n >= 0)
		return (print_pos(n, d));
	else
		return (print_neg(n, d));
}
