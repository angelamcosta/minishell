/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/09/21 15:44:58 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer(void);

void	lexer(void)
{
	int		i;
	int		j;
	char	*input;
	int		start;

	i = 0;
	j = 0;
	trim_argument(&term()->command);
	input = term()->command;
	term()->cmd_table = malloc(sizeof(char *) * (MAX_TOKENS + 1));
	while (input[i] && j < MAX_TOKENS)
	{
		start = i;
		if (input[i] == '|' || input[i] == '&')
			handle_token(&i, &j);
		else
		{
			while (input[i] && !((input[i] == '|' || input[i] == '&')
					&& !(is_inside_quotes(input, i))))
				i++;
			add_cmd(input, start, i, &j);
		}
	}
	term()->cmd_table[j] = NULL;
	parser();
}
