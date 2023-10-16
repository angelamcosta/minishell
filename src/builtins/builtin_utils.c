/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:52:47 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 20:00:54 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_varname(char *str);

int	is_valid_varname(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
	}
	return (1);
}
