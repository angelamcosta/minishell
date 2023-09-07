/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:36:42 by anlima            #+#    #+#             */
/*   Updated: 2023/09/07 17:10:04 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_argument(char *arg);
int	is_valid_command(const char *token);

int	is_valid_argument(char *arg)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = -1;
	single_quotes = 0;
	double_quotes = 0;
	while (arg[++i])
	{
		if (arg[i] == '"')
			double_quotes = !double_quotes;
		else if (arg[i] == '\'')
			single_quotes = !single_quotes;
	}
	if (double_quotes || single_quotes)
	{
		printf("Error: Mismatched quotes in argument: %s\n", arg);
		return (0);
	}
	return (1);
}

int	is_valid_command(const char *token)
{
	int			i;
	static char	*valid_commands[] = {"ls", "echo",
		"grep", "cat", "cd", "pwd", "|", "clear", "exit", NULL};

	i = -1;
	while (valid_commands[++i])
	{
		if (ft_strncmp(token, valid_commands[i],
				ft_strlen(valid_commands[i])) == 0)
			return (1);
	}
	printf("Error: Invalid command: %s\n", token);
	return (0);
}
