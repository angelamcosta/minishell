/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:18:08 by anlima            #+#    #+#             */
/*   Updated: 2023/09/06 14:05:54 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	trim_argument(char **arg);
void	handle_token(int *i, int *j);
int		is_token(char *input, int i);
void	handle_quotes(int *i, int *j);
void	toggle_state(char *input, int i, int *single_quotes,
			int *double_quotes);

void	trim_argument(char **arg)
{
	int		len;
	int		start;
	int		end;
	char	*trimmed;

	len = ft_strlen(*arg);
	start = 0;
	end = len - 1;
	while ((*arg)[start] == ' ')
		start++;
	while (end >= 0 && (*arg)[end] == ' ')
		end--;
	if (end >= start)
	{
		trimmed = ft_substr(*arg, start, end - start + 1);
		free(*arg);
		*arg = trimmed;
	}
}

void	handle_token(int *i, int *j)
{
	char	*input;

	input = term()->command;
	if ((input[*i] == input[*i + 1]) && input[*i + 1] != '|')
	{
		(term()->cmd_table[(*j)++]) = ft_substr(input, *i, 2);
		(*i) += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '&')
	{
		(term()->cmd_table[(*j)++]) = ft_substr(input, *i, 2);
		(*i) += 2;
	}
	else
	{
		(term()->cmd_table[(*j)++]) = ft_substr(input, *i, 1);
		(*i)++;
	}
}

int	is_token(char *input, int i)
{
	if ((input[i + 1] && input[i + 1] == ' '))
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			return (input[i]);
	}
	return (0);
}

void	handle_quotes(int *i, int *j)
{
	int		start;
	char	quote;
	char	*input;

	input = term()->command;
	quote = input[*i];
	start = (*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
	{
		(term()->cmd_table[(*j)++]) = ft_substr(input, start - 1, *i - start
				+ 2);
		trim_argument(&(term()->cmd_table[(*j) - 1]));
		(*i)++;
	}
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
