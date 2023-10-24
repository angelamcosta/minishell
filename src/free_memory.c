/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:58 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 19:24:34 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_mallocs(void);
void	free_reds(t_command *cmd);
void	free_token(t_token *token);
void	free_command(t_command *cmd);
void	free_term(t_term *term);

void	clean_mallocs(void)
{
	free_term(term());
}

void	free_token(t_token *token)
{
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(token);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	i = -1;
	while (++i < MAX_TOKENS && cmd->args[i])
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
	}
	i = -1;
	while (++i < LEN && cmd->delimiters[i])
	{
		free(cmd->delimiters[i]);
		cmd->delimiters[i] = NULL;
	}
	i = -1;
	while (++i < LEN && cmd->order[i])
	{
		free(cmd->order[i]);
		cmd->order[i] = NULL;
	}
}

void	free_term(t_term *term)
{
	int	i;

	i = -1;
	if (term->command)
	{
		free(term->command);
		term->command = NULL;
	}
	if (term->tokens)
	{
		while (++i < MAX_TOKENS && term->tokens[i])
		{
			free_token(term->tokens[i]);
			term->tokens[i] = NULL;
		}
		free(term->tokens);
		term->tokens = NULL;
	}
	i = -1;
	while (++i < MAX_TOKENS)
	{
		free_command(&term->cmd_list[i]);
		free_reds(&term->cmd_list[i]);
	}
}

void	free_reds(t_command *cmd)
{
	int	i;

	i = -1;
	while (++i < LEN && cmd->in_red[i])
	{
		free(cmd->in_red[i]);
		cmd->in_red[i] = NULL;
	}
	i = -1;
	while (++i < LEN && cmd->out_red[i])
	{
		free(cmd->out_red[i]);
		cmd->out_red[i] = NULL;
	}
	i = -1;
	while (++i < LEN && cmd->append[i])
	{
		free(cmd->append[i]);
		cmd->append[i] = NULL;
	}
}
