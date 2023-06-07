/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:02:45 by anlima            #+#    #+#             */
/*   Updated: 2023/06/08 00:24:18 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char	*str, char	*cmp, int n);

int	ft_strncmp(char	*str, char	*cmp, int n)
{
	int	i;

	i = -1;
	while (str[++i] && i < n)
	{
		if (cmp[i] && str[i] != cmp[i])
			break ;
	}
	return (str[i] == cmp[i]);
}
