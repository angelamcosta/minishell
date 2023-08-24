/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:48:52 by anlima            #+#    #+#             */
/*   Updated: 2023/08/23 13:01:41 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize_input(void);

void	tokenize_input(void)
{
	int	i;
	int	j;
	int	k;
	int	in_quotes;

	i = 0;
	j = 0;
	k = 0;
	in_quotes = 0;
	term()->arguments = malloc(sizeof(char *) * (MAX_TOKENS + 1));
	if (!term()->arguments)
		exit(EXIT_FAILURE);
	while (term()->command[i] && j < MAX_TOKENS)
	{
		while (term()->command[i] == ' ')
			i++;
		if (!term()->command[i])
			break ;
		term()->arguments[j] = malloc(MAX_TOKEN_LENGTH + 1);
		if (!term()->arguments[j])
			exit(EXIT_FAILURE);
		k = 0;
		while (term()->command[i] && (term()->command[i] != ' ' || in_quotes)
			&& k < MAX_TOKEN_LENGTH)
		{
			if (term()->command[i] == '"')
				in_quotes = !in_quotes;
			term()->arguments[j][k++] = term()->command[i++];
		}
		term()->arguments[j][k] = '\0';
		if (in_quotes)
		{
			fprintf(stderr, "Error: Mismatched quotes\n");
			exit(EXIT_FAILURE);
		}
		j++;
	}
	term()->arguments[j] = NULL;
}
