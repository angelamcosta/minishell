/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/10/09 16:57:47 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);
void	execute_red(t_command *cmd);
void	execute_command(t_command *cmd, char *path);
void	execute_in(t_command *cmd, char *filename, char *path);
void	execute_out(t_command *cmd, char *filename, char *path, int flag);

void	executor(void)
{
	int		i;
	int		j;
	int		fd_in;
	int		fd_out;
	pid_t	*child_pids;

	fd_in = STDIN_FILENO;
	fd_out = dup(STDOUT_FILENO);
	i = -1;
	j = -1;
	child_pids = malloc(term()->count_cmd * sizeof(pid_t));
	while (++i < term()->count_cmd)
	{
		while (term()->cmd_list[i].delimiters[++j])
			heredoc(term()->cmd_list[i].delimiters[j]);
		if (i == term()->count_cmd - 1 && (is_builtin(term()->cmd_list[i].name)))
		{
			execute_red(&term()->cmd_list[i]);
			execute_builtin(&term()->cmd_list[i]);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			break ;
		}
		if (i < term()->count_cmd - 1)
		{
			create_pipe();
			child_pids[i] = create_fork(&term()->cmd_list[i], fd_in,
					term()->pipe_fd[1]);
			close(term()->pipe_fd[1]);
			fd_in = term()->pipe_fd[0];
		}
		else
		{
			child_pids[i] = create_fork(&term()->cmd_list[i], fd_in,
					STDOUT_FILENO);
			if (fd_in != STDIN_FILENO)
				close(fd_in);
		}
	}
	i = -1;
	while (++i < term()->count_cmd)
	{
		if (child_pids[i] > 0)
			waitpid(child_pids[i], NULL, 0);
	}
	free(child_pids);
}

void	execute_red(t_command *cmd)
{
	int		i;
	char	*path;

	path = get_path(cmd->name);
	i = -1;
	while (cmd->in_red[++i])
		execute_in(cmd, cmd->in_red[i], path);
	i = -1;
	while (cmd->append[++i])
		execute_out(cmd, cmd->append[i], path, 1);
	i = -1;
	while (cmd->out_red[++i])
		execute_out(cmd, cmd->out_red[i], path, 0);
	if (!is_builtin(cmd->name))
		execute_command(cmd, path);
}

void	execute_command(t_command *cmd, char *path)
{
	if (!cmd->name)
		exit(EXIT_SUCCESS);
	if (access(path, X_OK) == -1)
	{
		fprintf(stderr, "%s: command not found\n", cmd->name);
		exit(NOT_FOUND);
	}
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

void	execute_out(t_command *cmd, char *filename, char *path, int flag)
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
	printf("DEBUG: Opened file %s with fd: %i\n", filename, out);
	dup2(out, STDOUT_FILENO);
	close(out);
}
