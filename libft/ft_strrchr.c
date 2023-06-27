/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:18:13 by anlima            #+#    #+#             */
/*   Updated: 2022/10/29 19:11:21 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	lens;

	lens = ft_strlen(s);
	while (lens > 0 && (unsigned char)s[lens] != (unsigned char)c)
		lens--;
	if ((unsigned char)s[lens] == (unsigned char)c)
		return ((char *)&s[lens]);
	return (0);
}
