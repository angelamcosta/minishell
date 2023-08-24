/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:18:08 by anlima            #+#    #+#             */
/*   Updated: 2023/08/24 14:45:47 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		is_token(char *input, int i);
int		trim_whitespaces(char *input, int i);
void	add_token(char *input, char **args, int i, int j);
void	toggle_state(char *input, int i, int *single_quotes,
			int *double_quotes);

void add_token(char *input, char **args, int i, int j)
{
	
}

int	trim_whitespaces(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

int	is_token(char *input, int i)
{
	if (input[i + 1] && input[i + 1] != ' ')
	{
		if (input[i] == '<' && input[i + 1] == '<')
			return (1);
		if (input[i] == '>' && input[i + 1] == '>')
			return (1);
	}
	else if ((input[i + 1] && input[i + 1] == ' '))
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			return (input[i]);
	}
	return (0);
}

void	toggle_state(char *input, int i, int *single_quotes, int *double_quotes)
{
	if (input[i] == '\'' && !single_quotes)
		*single_quotes = 1;
	else if (input[i] == '\'' && single_quotes)
		*single_quotes = 0;
	if (input[i] == '"' && !double_quotes)
		*double_quotes = 1;
	else if (input[i] == '"' && double_quotes)
		*double_quotes = 0;
}
