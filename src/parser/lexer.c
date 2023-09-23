/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/09/23 22:48:24 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer(void);
void	add_token(char *input, int i, int flag);

void	lexer(void)
{
	int		i;
	char	**input;

	i = 0;
	input = ft_split(term()->command, ' ');
	term()->tokens = (t_token **)malloc(sizeof(t_token *) * (MAX_TOKENS + 1));
	while (input[i] && i < MAX_TOKENS)
	{
		if (i == 0 || (input[i - 1] && (ft_strncmp(input[i - 1], "|", 1) == 0
					|| ft_strncmp(input[i - 1], "&", 1) == 0)))
			add_token(input[i], i, 1);
		else
			add_token(input[i], i, 0);
		i++;
	}
	term()->tokens[i] = NULL;
}

void	add_token(char *input, int i, int flag)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (flag)
		token->type = CMD;
	else if (ft_strncmp(input, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(input, "<<", 2) == 0)
		token->type = HEREDOC;
	else if (input[0] == '|' || input[0] == '&')
		token->type = PIPE;
	else if (input[0] == '<')
		token->type = RED_IN;
	else if (input[0] == '>')
		token->type = RED_OUT;
	else if (input[0] == '$')
		token->type = VAR;
	else
		token->type = ARG;
	token->value = ft_strdup(input);
	term()->tokens[i] = token;
}
