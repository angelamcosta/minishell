/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/10/23 23:48:14 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer(void);
void	parser(void);
void	aux_parser(int *i, int j);

void	lexer(void)
{
	if (!check_quotes(term()->command))
	{
		printf("parse error; unbalanced quotes\n");
		g_exit = EXIT_FAILURE;
		return ;
	}
	if (read_string())
	{
		tokenize_input();
		grammar();
	}
}

void	parser(void)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (term()->tokens[++i])
	{
		if (term()->tokens[i]->type == CMD)
		{
			if (i > 0)
				j++;
			add_command(&term()->cmd_list[j], &term()->tokens[i]);
		}
		else if (term()->tokens[i]->type == ARG)
			add_argument(&term()->cmd_list[j], term()->tokens[i]->value);
		else
			aux_parser(&i, j);
	}
	executor();
}

void	aux_parser(int *i, int j)
{
	if (term()->tokens[*i]->type == HEREDOC)
		add_red(term()->cmd_list[j].delimiters, term()->tokens[++(*i)]->value,
			term()->cmd_list[j].order);
	else if (term()->tokens[*i]->type == RED_IN)
		add_red(term()->cmd_list[j].in_red, term()->tokens[++(*i)]->value,
			term()->cmd_list[j].order);
	else if (term()->tokens[*i]->type == APPEND)
		add_red(term()->cmd_list[j].append, term()->tokens[++(*i)]->value,
			term()->cmd_list[j].order);
	else if (term()->tokens[*i]->type == RED_OUT)
		add_red(term()->cmd_list[j].out_red, term()->tokens[++(*i)]->value,
			term()->cmd_list[j].order);
}
