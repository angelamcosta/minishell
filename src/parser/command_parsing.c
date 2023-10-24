/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 17:11:36 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_split_pipes(char *input);
void	add_argument(t_command *cmd, char *value);
void	add_command(t_command *cmd, t_token **tokens);
void	trim_whitespaces(char *input, int *i, int quote);
void	add_red(char **cmd_list, char *value, char **order);

void	add_argument(t_command *cmd, char *value)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL && i < MAX_TOKENS)
		i++;
	if (i < MAX_TOKENS)
	{
		if ((cmd->name) && !((ft_strncmp(cmd->name, "echo", 5) == 0)
				|| (ft_strncmp(cmd->name, "export", 7) == 0)
				|| (ft_strncmp(cmd->name, "exit", 5) == 0)))
			cmd->args[i] = dup_quoted(value);
		else
			cmd->args[i] = ft_strdup(value);
	}
}

void	add_red(char **cmd_list, char *value, char **order)
{
	int	i;

	i = 0;
	while (cmd_list[i] != NULL && i < MAX_TOKENS)
		i++;
	if (i < MAX_TOKENS)
		cmd_list[i] = dup_quoted(value);
	i = 0;
	while (order[i] != NULL && i < MAX_TOKENS)
		i++;
	if (i < MAX_TOKENS)
		order[i] = dup_quoted(value);
}

void	add_command(t_command *cmd, t_token **tokens)
{
	cmd->name = ft_strdup((*tokens)->value);
	cmd->args[0] = ft_strdup((*tokens)->value);
	cmd->in_red[0] = NULL;
	cmd->out_red[0] = NULL;
}

char	**ft_split_pipes(char *input)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	**result;

	i = -1;
	k = -1;
	quote = 0;
	result = (char **)malloc(sizeof(char *) * (count_pipes(input) + 2));
	while (++i < (int)ft_strlen(input))
	{
		trim_whitespaces(input, &i, quote);
		j = i - 1;
		while (input[++i])
		{
			if (input[i] == '|' && quote == 0)
				break ;
			if (input[i] == '"' || input[i] == '\'')
				change_quote(&quote, input[i]);
		}
		result[++k] = ft_substr(input, j, i - j);
	}
	result[++k] = NULL;
	return (result);
}

void	trim_whitespaces(char *input, int *i, int quote)
{
	while (input[++(*i)] == ' ' && quote == 0)
		;
}
