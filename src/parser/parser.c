/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/05 15:09:34 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);

void	parser(void)
{
	int		i;
	char	**tokens;

	tokens = term()->cmd_table;
	i = 0;
	if (!is_valid_command(tokens[i]))
	{
		printf("Error: Invalid command: %s\n", tokens[i]);
		return ;
	}
	while (tokens[i] != NULL)
	{
		if (!is_valid_argument(tokens[i]))
			return ;
		i++;
	}
}
