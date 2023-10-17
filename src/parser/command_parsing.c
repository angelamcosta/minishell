/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/10/17 14:08:56 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_commands(void);
char	**ft_split_pipes(char *input);
void	add_red(char **cmd_list, char *value);
void	add_argument(t_command *cmd, char *value);
void	add_command(t_command *cmd, t_token **tokens);

void	count_commands(void)
{
	int			i;
	int			flag;
	t_command	*cmd_list;

	i = 0;
	flag = 1;
	cmd_list = term()->cmd_list;
	while (flag)
	{
		flag = 0;
		if ((cmd_list[i].name != NULL) || (cmd_list[i].args[0] != NULL)
			|| (cmd_list[i].in_red[0] != NULL)
			|| (cmd_list[i].out_red[0] != NULL)
			|| (cmd_list[i].delimiters[0] != NULL)
			|| (cmd_list[i].append[0] != NULL))
			flag = 1;
		if (flag)
			++i;
	}
	term()->count_cmd = i;
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

	i = count_pipes(input);
	result = (char **)malloc(sizeof(char *) * (i + 1));
	k = -1;
	i = -1;
	quote = 0;
	while (++i < (int)ft_strlen(input))
	{
		while (input[i] == ' ' && quote == 0)
			i++;
		j = i;
		while (input[i])
		{
			if (input[i] == '|' && quote == 0)
				break ;
			if (input[i] == '"' || input[i] == '\'')
				change_quote(&quote, input[i]);
			i++;
		}
		result[++k] = ft_substr(input, j, i - j);
	}
	result[++k] = NULL;
	return (result);
}
