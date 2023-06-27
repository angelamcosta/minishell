/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:32:12 by anlima            #+#    #+#             */
/*   Updated: 2022/10/29 19:11:06 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lend;
	size_t	lens;
	size_t	i;

	lens = ft_strlen(src);
	if (!size)
		return (lens);
	lend = ft_strlen(dst);
	i = lend;
	if (size > 0 && size > lend)
	{
		while (*src && (i < size - 1))
			dst[i++] = *src++;
		dst[i] = '\0';
		return (lend + lens);
	}
	return (lens + size);
}
