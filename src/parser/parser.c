/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/16 16:59:31 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);

void	parser(void)
{
	int		i;
	int		flag;
	char	**input;

	i = -1;
	flag = 0;
	input = term()->cmd_table;
	while (input[++i])
	{
		if (!is_valid_argument(input[i]) || !is_valid_red(input, i))
		{
			flag = 1;
			break ;
		}
	}
	if (input[i] && flag)
		handle_error(input, i);
	else
		executor();
}
