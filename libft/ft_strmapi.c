/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:18:50 by anlima            #+#    #+#             */
/*   Updated: 2022/10/29 19:09:23 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s1;
	int		i;

	if (!s || !f)
		return (NULL);
	s1 = (char *)malloc(ft_strlen(s) + 1);
	if (!s1)
		return (NULL);
	i = -1;
	while (s[++i])
		s1[i] = f(i, s[i]);
	s1[i] = '\0';
	return (s1);
}
