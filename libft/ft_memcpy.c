/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:37:51 by anlima            #+#    #+#             */
/*   Updated: 2022/10/19 17:01:44 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dest && !src)
		return (NULL);
	i = -1;
	d = (char *)dest;
	s = (char *)src;
	while (++i < n)
		d[i] = s[i];
	return (dest);
}
