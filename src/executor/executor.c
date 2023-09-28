/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/09/28 18:17:13 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);
void	execute_red(t_command *cmd);
void	execute_command(t_command *cmd, char *path);
void	execute_in(t_command *cmd, char *filename, char *path);
void	execute_out(t_command *cmd, char *filename, char *path);

void	executor(void)
{
	int	i;
	int	fd_in;

	fd_in = STDIN_FILENO;
	i = -1;
	while (term()->cmd_list[++i].name)
	{
		if (is_builtin(term()->cmd_list[i].name))
		{
			set_pipes(fd_in, STDOUT_FILENO);
			execute_builtin(&term()->cmd_list[i]);
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			continue ;
		}
		if (term()->cmd_list[i + 1].name)
		{
			create_pipe();
			create_fork(&term()->cmd_list[i], fd_in, term()->pipe_fd[1]);
			close(term()->pipe_fd[1]);
			fd_in = term()->pipe_fd[0];
		}
		else
		{
			create_fork(&term()->cmd_list[i], fd_in, STDOUT_FILENO);
			if (i != 0)
				close(fd_in);
		}
	}
}

void	execute_red(t_command *cmd)
{
	int		i;
	char	*path;
	char	**in_red;
	char	**out_red;

	path = ft_strdup(get_path(cmd->name));
	if (cmd->in_red[0] != NULL || cmd->out_red[0] != NULL)
	{
		out_red = cmd->out_red;
		in_red = cmd->in_red;
		i = -1;
		term()->in_cmd = 1;
		while (cmd->in_red[++i])
			execute_in(cmd, cmd->in_red[i], path);
		i = -1;
		while (cmd->out_red[++i])
			execute_out(cmd, cmd->out_red[i], path);
		term()->in_cmd = 0;
	}
	execute_command(cmd, path);
}

void	execute_command(t_command *cmd, char *path)
{
	// printf("Path: %s\nArgs: %s\n", path, cmd->args[0]);
	execve(path, cmd->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	execute_in(t_command *cmd, char *filename, char *path)
{
	int	in;

	in = open(filename, O_RDONLY);
	if (in == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(in, STDIN_FILENO);
	close(in);
}

void	execute_out(t_command *cmd, char *filename, char *path)
{
	int	out;

	out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(out, STDOUT_FILENO);
	close(out);
}
