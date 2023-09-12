/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/12 16:13:05 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);

void	parser(void)
{
	int			i;
	char		**input;

	i = 0;
	input = term()->cmd_table;
	while (input[i])
	{
		if (!is_valid_command(input[i]) || !(is_valid_argument(input[i]))
			|| !(is_valid_red(input, i)))
			return ;
		insert_node(&term()->command_tree, input[i]);
		i++;
	}
	print_commands(term()->command_tree);
}
