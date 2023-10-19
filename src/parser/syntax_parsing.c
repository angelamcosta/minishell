/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:12:43 by mpedroso          #+#    #+#             */
/*   Updated: 2023/10/19 23:01:09 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	grammar(void);
int		read_string(void);
int		check_quotes(char *str);
int		should_expand(char *input);
void	change_quote(int *quote, char input);

void	grammar(void)
{
	int		i;
	t_token	**tokens;

	i = -1;
	tokens = term()->tokens;
	while (tokens && tokens[++i])
	{
		if ((tokens[i]->type == APPEND || tokens[i]->type == HEREDOC
				|| tokens[i]->type == RED_IN || tokens[i]->type == RED_OUT))
		{
			if (!tokens[i + 1])
			{
				printf("syntax error near unexpected token `newline`\n");
				g_exit = EXIT_FAILURE;
				return ;
			}
			else if (tokens[i + 1]->type == PIPE || tokens[i + 1]->type == CMD)
			{
				printf("syntax error near unexpected token `|`\n");
				g_exit = EXIT_FAILURE;
				return ;
			}
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
			change_quote(&quote, input[i]);
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
				g_exit = EXIT_FAILURE;
				return (0);
			}
			while (term()->command[++i] && term()->command[i] == ' ')
				;
			if (term()->command[i] == '|')
			{
				printf("parse error near `%c`\n", term()->command[i]);
				g_exit = EXIT_FAILURE;
				return (0);
			}
			i--;
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

void	change_quote(int *quote, char input)
{
	if (*quote == 0)
		*quote = input;
	else if (*quote == input)
		*quote = 0;
}
