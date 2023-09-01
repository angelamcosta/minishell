/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/09/01 15:00:32 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '=');
}

void	parser(void)
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
		if (is_special_char(input[i]))
			handle_token(&i, &j);
		else if (input[i] == '"' || input[i] == '\'')
			handle_quotes(&i, &j);
		else
		{
			while (input[i] && !is_special_char(input[i]))
				i++;
			(term()->cmd_table[j++]) = ft_substr(input, start, i - start);
			trim_argument(&(term()->cmd_table[j - 1]));
		}
	}
	term()->cmd_table[j] = NULL;
}
