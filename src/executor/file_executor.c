/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:06:45 by anlima            #+#    #+#             */
/*   Updated: 2023/10/22 17:35:14 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_in(char *filename);
char	*execute_red(t_command *cmd);
void	execute_out(char *filename, int flag);

void	execute_in(char *filename)
{
	int	in;

	in = open(filename, O_RDONLY);
	if (in == -1)
		exit(EXIT_FAILURE);
	dup2(in, STDIN_FILENO);
	close(in);
}

char	*execute_red(t_command *cmd)
{
	int		i;
	char	*path;

	if (cmd->name && (cmd->name[0] == '/' || (ft_strncmp(cmd->name, "./",
					2) == 0)))
		path = ft_strdup(cmd->name);
	else if (is_builtin(cmd->name))
		path = NULL;
	else
		path = get_path(cmd->name);
	i = -1;
	while (cmd->in_red[++i])
		execute_in(cmd->in_red[i]);
	i = -1;
	while (cmd->append[++i])
		execute_out(cmd->append[i], 1);
	i = -1;
	while (cmd->out_red[++i])
		execute_out(cmd->out_red[i], 0);
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
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(out, STDOUT_FILENO);
	close(out);
}
