/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:34:41 by anlima            #+#    #+#             */
/*   Updated: 2022/10/13 09:37:22 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcount(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n / 10 > 0 && i++)
		n = n / 10;
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	nb;
	char	*str;

	nb = n;
	len = ft_charcount(nb) + 1;
	str = (char *)malloc(len);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	str[--len] = '\0';
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[--len] = nb % 10 + 48;
		nb /= 10;
	}
	return (str);
}
