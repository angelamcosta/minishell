/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/24 19:37:16 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);
void	add_red(char **cmd_list, char *value);
void	add_argument(t_command *cmd, char *value);
void	handle_variables(t_command *cmd, char *value);
void	add_command(t_command *cmd, t_token **tokens);

void	parser(void)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (term()->tokens[++i])
	{
		if (term()->tokens[i]->type == PIPE)
			i++;
		if (term()->tokens[i]->type == CMD)
		{
			j++;
			add_command(&term()->cmd_list[j], &term()->tokens[i]);
		}
		else if (term()->tokens[i]->type == ARG)
			add_argument(&term()->cmd_list[j], term()->tokens[i]->value);
		else if (term()->tokens[i]->type == HEREDOC)
			add_red(term()->cmd_list[j].delimiters, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == RED_IN)
			add_red(term()->cmd_list[j].in_red, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == RED_OUT)
			add_red(term()->cmd_list[j].out_red, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == VAR)
			handle_variables(&term()->cmd_list[j], term()->tokens[i]->value);
	}
}

void	add_argument(t_command *cmd, char *value)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL && i < MAX_TOKENS)
		i++;
	if (i < MAX_TOKENS)
		cmd->args[i] = ft_strdup(value);
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

void	handle_variables(t_command *cmd, char *value)
{
	int		i;
	int		flag;
	char	*var_name;

	i = -1;
	flag = 0;
	var_name = value + 1;
	while (term()->env[++i] != NULL && !flag)
	{
		if (ft_strncmp(term()->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			flag = 1;
			break ;
		}
	}
	if (flag)
		add_argument(cmd, term()->env[i] + ft_strlen(var_name) + 1);
}

void	add_command(t_command *cmd, t_token **tokens)
{
	cmd->name = ft_strdup((*tokens)->value);
	cmd->args[0] = NULL;
	cmd->in_red[0] = NULL;
	cmd->out_red[0] = NULL;
}
