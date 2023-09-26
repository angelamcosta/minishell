/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:12:43 by mpedroso          #+#    #+#             */
/*   Updated: 2023/09/26 14:44:10 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	grammar_check(int i)
{
	t_token	**tokens;

	tokens = term()->tokens;
	if (tokens[i] && (tokens[i]->type != CMD && tokens[i]->type != ARG
			&& tokens[i]->type != VAR))
	{
		if (!tokens[i + 1])
			return (0);
		if (tokens[i + 1] && (tokens[i + 1]->type != CMD 
				&& tokens[i + 1]->type != ARG 
				&& tokens[i + 1]->type != VAR))
			return (0);
	}
	return (1);
}
