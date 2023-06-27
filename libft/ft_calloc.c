/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:33:27 by anlima            #+#    #+#             */
/*   Updated: 2022/11/01 09:08:44 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*arr;

	arr = (void *)malloc(num * size);
	if (!arr)
		return (NULL);
	ft_memset(arr, 0, num * size);
	return (arr);
}
