/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:12:43 by mpedroso          #+#    #+#             */
/*   Updated: 2023/10/17 10:20:26 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	grammar(void);
int		read_string(void);
int		check_quotes(char *str);
int		should_expand(char *input);

void	grammar(void)
{
	int		i;
	t_token	**tokens;

	i = -1;
	tokens = term()->tokens;
	while (tokens && tokens[++i])
	{
		if ((i == 0 && tokens[i]->value[0] == '|') || ((tokens[i + 1])
				&& tokens[i]->type == PIPE && tokens[i + 1]->type == PIPE))
		{
			printf("parse error near `%s`\n", tokens[i]->value);
			term()->exit_status = EXIT_FAILURE;
			return ;
		}
	}
	parser();
}

int	should_expand(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		if (input[i] == '$' && (quote == 0 || quote == '"'))
		{
			if ((input[i + 1] != '\0' && input[i + 1] != ' ' && quote == 0)
				|| (quote == '"' && input[i + 1] != ' ' && input[i + 1] != '"'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	read_string(void)
{
	int	i;

	i = -1;
	while (term()->command[++i])
	{
		if (term()->command[i] == '|')
		{
			if (i == 0 || (i > 0 && term()->command[i - 1] == '|'))
			{
				printf("parse error near `%c`\n", term()->command[i]);
				term()->exit_status = EXIT_FAILURE;
				return (0);
			}
		}
	}
	return (1);
}

int	check_quotes(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str && str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i];
		else if ((str[i] == '"' || str[i] == '\'') && quote == str[i])
			quote = 0;
	}
	if (quote != 0)
		return (0);
	return (1);
}
