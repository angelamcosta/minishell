/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:31:26 by anlima            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:31 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(char *input);

int	count_pipes(char *input)
{
	int	i;
	int	count;
	int	quote;

	i = -1;
	quote = 0;
	count = 0;
	while (input[++i])
	{
		while (input[i] == ' ' && quote == 0)
			i++;
		if (input[i] == '"' || input[i] == '\'')
			change_quote(&quote, input[i]);
		if ((input[i] == '|' || input[i] == '\0') && quote == 0)
			count++;
	}
	return (count);
}
