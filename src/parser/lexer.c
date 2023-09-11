/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/09/11 17:04:29 by anlima           ###   ########.fr       */
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
	input = term()->command;
	term()->cmd_table = malloc(sizeof(char *) * (MAX_TOKENS + 1));
	while (input[i] && j < MAX_TOKENS)
	{
		start = i;
		if (input[i] == '|' || input[i] == '&')
			handle_token(&i, &j);
		else if (input[i] == '"' || input[i] == '\'')
			handle_quotes(&i, &j);
		else
		{
			while (input[i] && input[i] != '|' && input[i] != '&')
				i++;
			(term()->cmd_table[j++]) = ft_substr(input, start, i - start);
			trim_argument(&(term()->cmd_table[j - 1]));
		}
	}
	term()->cmd_table[j] = NULL;
}
