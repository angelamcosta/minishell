/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:49:03 by anlima            #+#    #+#             */
/*   Updated: 2022/10/29 19:11:35 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	subs = (char *)malloc(len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		subs[i++] = s[start++];
	subs[i] = '\0';
	return (subs);
}
