/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:06:45 by anlima            #+#    #+#             */
/*   Updated: 2023/10/23 23:44:55 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_in(char *filename);
void	red_priority(t_command *cmd);
char	*execute_red(t_command *cmd);
void	execute_out(char *filename, int flag);

void	execute_in(char *filename)
{
	int	in;

	in = open(filename, O_RDONLY);
	if (in == -1)
	{
		g_exit = EXIT_FAILURE;
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(in, STDIN_FILENO);
	close(in);
}

char	*execute_red(t_command *cmd)
{
	char	*path;

	if (cmd->name && (cmd->name[0] == '/' || (ft_strncmp(cmd->name, "./",
					2) == 0)))
		path = ft_strdup(cmd->name);
	else if (is_builtin(cmd->name))
		path = NULL;
	else
		path = get_path(cmd->name);
	red_priority(cmd);
	return (path);
}

void	execute_out(char *filename, int flag)
{
	int	out;

	if (flag)
		out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out == -1)
	{
		g_exit = EXIT_FAILURE;
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	red_priority(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->order[i] != NULL)
	{
		if (is_in_red(cmd, cmd->order[i]))
			execute_in(cmd->order[i]);
		else if (is_out_red(cmd, cmd->order[i]))
			execute_out(cmd->order[i], 0);
		else if (is_append(cmd, cmd->order[i]))
			execute_out(cmd->order[i], 1);
		i++;
	}
}
