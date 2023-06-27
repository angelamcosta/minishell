/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:24:17 by anlima            #+#    #+#             */
/*   Updated: 2022/10/29 18:37:21 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	temp;
	int			signal;

	signal = 1;
	temp = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		temp = temp * 10 + (*str++ - 48);
		if (temp > 2147483648 && signal > 0)
			return (-1);
		else if (temp > 2147483648 && signal < 0)
			return (0);
	}
	return (temp * signal);
}
