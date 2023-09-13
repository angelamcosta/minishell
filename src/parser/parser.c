/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/13 16:18:29 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);

void	parser(void)
{
	int		i;
	char	**input;

	i = 0;
	input = term()->cmd_table;
	while (input[i])
	{
		if (!is_valid_argument(input[i]) || !is_valid_red(input, i))
			break ;
		insert_node(&term()->command_tree, input[i]);
		i++;
	}
	if (i > 0 && ft_strncmp(input[i - 1], " ", 1) == 0)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (input[i] && ((!is_valid_argument(input[i]) || !is_valid_red(input,
					i))))
	{
		if (!is_valid_argument(input[i]))
			handle_quotes();
		else
			handle_red();
		lexer();
	}
	else
		print_commands(term()->command_tree);
}
