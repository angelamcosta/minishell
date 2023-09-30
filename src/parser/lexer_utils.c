/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:12:43 by mpedroso          #+#    #+#             */
/*   Updated: 2023/09/30 13:20:40 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
