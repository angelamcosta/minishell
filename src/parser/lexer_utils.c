/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:18:08 by anlima            #+#    #+#             */
/*   Updated: 2023/09/16 17:00:01 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	trim_argument(char **arg);
void	handle_token(int *i, int *j);
void	handle_error(char **input, int i);
int		is_inside_quotes(char *input, int i);
void	add_cmd(char *input, int start, int i, int *j);

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
	if ((input[*i] == input[*i + 1]) && (input[*i + 1] == '|' || input[*i
				+ 1] == '&'))
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

void	handle_error(char **input, int i)
{
	if (i > 1 && ft_strncmp(input[i], "|", 1) == 0 && ft_strncmp(input[i],
			input[i - 1], 1) == 0)
		printf("bash: syntax error near unexpected token `|'\n");
	else
	{
		if (!is_valid_argument(input[i]))
			handle_quotes();
		else
			handle_red();
		lexer();
	}
}

int	is_inside_quotes(char *input, int j)
{
	int		i;
	char	quote;
	int		opened;

	i = 0;
	opened = 0;
	while (input[i] && i < j)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (opened == 0)
				opened = input[i];
			else if (opened == input[i])
				opened = 0;
		}
		i++;
	}
	return (opened);
}

void	add_cmd(char *input, int start, int i, int *j)
{
	if (input[start] == ' ' && (i - start) == 1)
		return ;
	(term()->cmd_table[(*j)++]) = ft_substr(input, start, i - start);
	trim_argument(&(term()->cmd_table[*j - 1]));
}
