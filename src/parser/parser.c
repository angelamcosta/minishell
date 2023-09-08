/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/08 13:30:29 by anlima           ###   ########.fr       */
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
	while (tokens[i])
	{
		if (!is_valid_command(tokens[i]) || !(is_valid_argument(tokens[i]))
			|| !(is_valid_red(tokens, i)))
			return ;
		i++;
	}
	executor();
}
