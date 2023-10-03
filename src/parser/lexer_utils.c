/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:12:43 by mpedroso          #+#    #+#             */
/*   Updated: 2023/10/03 11:57:53 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		read_string(void);
int		grammar_check(int i);
char	*get_var_name(char *value);

int	grammar_check(int i)
{
	t_token	**tokens;

	tokens = term()->tokens;
	if (tokens[i] && (tokens[i]->type != CMD && tokens[i]->type != ARG
			&& tokens[i]->type != VAR))
	{
		if (!tokens[i + 1])
			return (0);
		if (tokens[i + 1] && (tokens[i + 1]->type != CMD && tokens[i
				+ 1]->type != ARG && tokens[i + 1]->type != VAR))
			return (0);
	}
	return (1);
}

char	*get_var_name(char *value)
{
	if (value[0] == '"')
		return (value + 2);
	return (value + 1);
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
