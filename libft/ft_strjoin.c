/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:56:00 by anlima            #+#    #+#             */
/*   Updated: 2022/10/20 10:41:57 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!joined)
		return (NULL);
	while (s1 && *s1)
		joined[i++] = *s1++;
	while (s2 && *s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}
