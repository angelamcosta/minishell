/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/10/13 17:22:05 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);
void	add_red(char **cmd_list, char *value);
void	add_argument(t_command *cmd, char *value);
char	*handle_variables(char *value);
void	add_command(t_command *cmd, t_token **tokens);

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
		else if (term()->tokens[i]->type == HEREDOC)
			add_red(term()->cmd_list[j].delimiters, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == RED_IN)
			add_red(term()->cmd_list[j].in_red, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == APPEND)
			add_red(term()->cmd_list[j].append, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == RED_OUT)
			add_red(term()->cmd_list[j].out_red, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == VAR)
			add_argument(&term()->cmd_list[j], term()->tokens[i]->value);
	}
	count_commands();
	executor();
}

void	add_argument(t_command *cmd, char *value)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i] != NULL && i < MAX_TOKENS)
		i++;
	if (i < MAX_TOKENS)
	{
		if (should_expand(value) && (ft_strncmp(cmd->args[0], "echo", 4) == 0))
		{
			expanded = expand_var(value);
			cmd->args[i] = ft_strdup(expanded);
		}
		else
			cmd->args[i] = ft_strdup(value);
	}
}

void	add_red(char **cmd_list, char *value)
{
	int	i;

	i = 0;
	while (cmd_list[i] != NULL && i < MAX_TOKENS)
		i++;
	if (i < MAX_TOKENS)
		cmd_list[i] = ft_strdup(value);
}

char	*handle_variables(char *value)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (ft_strncmp(value, "?", 2) == 0)
		return (ft_itoa(term()->exit_status));
	while (term()->env[++i] != NULL && !flag)
	{
		if (ft_strncmp(term()->env[i], value, ft_strlen(value)) == 0)
		{
			flag = 1;
			break ;
		}
	}
	if (flag)
		return (term()->env[i] + ft_strlen(value) + 1);
	else
		return (NULL);
}

void	add_command(t_command *cmd, t_token **tokens)
{
	cmd->name = ft_strdup((*tokens)->value);
	cmd->args[0] = ft_strdup((*tokens)->value);
	cmd->in_red[0] = NULL;
	cmd->out_red[0] = NULL;
}
