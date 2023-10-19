/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/10/19 20:00:39 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_commands(void);
char	**ft_split_pipes(char *input);
void	add_red(char **cmd_list, char *value);
void	add_argument(t_command *cmd, char *value);
void	add_command(t_command *cmd, t_token **tokens);

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
		cmd_list[i] = dup_quoted(value);
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
