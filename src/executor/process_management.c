/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:42 by anlima            #+#    #+#             */
/*   Updated: 2023/10/20 15:16:18 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fork(void);
int		create_pipe(void);
void	create_fork(void);
int		set_pipes(t_command *cmd);
void	close_pipes(t_command *cmd);

int	create_pipe(void)
{
	int			*fd;
	t_command	*list;

	list = term()->cmd_list;
	while (list)
	{
		if (list->pipe_output || (list->prev && list->prev->pipe_output))
		{
			fd = (int *)malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
				return (0);
			list->pipe_fd = fd;
		}
		list = list->next;
	}
	return (1);
}

void	create_fork(void)
{
	t_command	*list;

	list = term()->cmd_list;
	while (list)
	{
		term()->pid = fork();
		if (term()->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (term()->pid == 0)
			execute_red(&list[0]);
		list = list->next;
	}
	close_fork();
}

int	set_pipes(t_command *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->prev && cmd->prev->pipe_output)
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
	if (cmd->pipe_output)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close_pipes(cmd);
	return (1);
}

void	close_pipes(t_command *cmd)
{
	t_command	*list;

	list = term()->cmd_list;
	while (list)
	{
		if (list != cmd && list->pipe_fd)
		{
			close(list->pipe_fd[0]);
			close(list->pipe_fd[1]);
		}
		list = list->next;
	}
}

void	close_fds(t_command *cmd)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	close_pipes(cmd);
}

void	close_fork(void)
{
	pid_t	pid;
	int		status;

	close_fds(&term()->cmd_list[0]);
	pid = 0;
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == term()->pid)
			g_exit = status;
	}
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
}
