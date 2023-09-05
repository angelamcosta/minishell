/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/02 11:54:33 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);

void	parser(void)
{
	int		i;
	char	**cmd_table;

	cmd_table = term()->cmd_table;
	i = 0;
	while (1)
	{
		if (cmd_table[i] == 0)
		{
			printf("[%s] ", cmd_table[i - 1]);
			break ;
		}
		if (is_special_char(cmd_table[i][0])
			|| cmd_table[i] == 0)
			printf("[%s] ", cmd_table[i - 1]);
		i++;
	}
	printf("\n");
}
