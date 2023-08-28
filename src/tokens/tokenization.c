/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/08/28 15:42:27 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	tokenization(void)
{
	int		i;
	int		j;
	char	*input;
	int		start;
	char	quote;

	i = 0;
	j = 0;
	input = term()->command;
	term()->arguments = malloc(sizeof(char *) * (MAX_TOKENS + 1));
	while (input[i] && j < MAX_TOKENS)
	{
		start = i;
		if (is_special_char(input[i]))
		{
			if ((input[i] == input[i + 1]) && input[i + 1] != '|')
			{
				(term()->arguments[j++]) = ft_substr(input, i, 2);
				i += 2;
			}
			else
			{
				(term()->arguments[j++]) = ft_substr(input, i, 1);
				i++;
			}
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			i++;
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
			{
				(term()->arguments[j++]) = ft_substr(input, start - 1, i - start
						+ 2);
				trim_argument(&(term()->arguments[j - 1]));
				i++;
			}
		}
		else
		{
			while (input[i] && !is_special_char(input[i]))
				i++;
			(term()->arguments[j++]) = ft_substr(input, start, i - start);
			trim_argument(&(term()->arguments[j - 1]));
		}
	}
	term()->arguments[j] = NULL;
}
