/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/08/23 16:18:43 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokenization(void);

void	tokenization(void)
{
	int		i;
	int		j;
	int		single_quotes;
	int		double_quotes;
	char	*input;

	i = -1;
	j = -1;
	single_quotes = 0;
	double_quotes = 0;
	input = term()->command;
	term()->arguments = malloc(sizeof(char *) * (MAX_TOKENS + 1));
	while (input[++i] && i < MAX_TOKENS)
	{
		i = trim_whitespaces(input, i);
		if (!input[i])
			break ;
		if (is_token(input, i))
			add_token(input, i);
		if (input[i] == '"' || input[i] == "'")
			toggle_state(input, i, &single_quotes, &double_quotes);
	}
}
