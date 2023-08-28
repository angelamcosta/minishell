/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:18:08 by anlima            #+#    #+#             */
/*   Updated: 2023/08/28 15:43:26 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	trim_argument(char **arg);
int		is_token(char *input, int i);
void	add_token(char *input, char **args, int i, int j);
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

void	add_token(char *input, char **args, int i, int j)
{
	args[++j] = ft_substr(input, i, 1);
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
