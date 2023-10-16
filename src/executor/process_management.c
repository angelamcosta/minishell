/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:42 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 15:39:04 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_pipe(void);
void	set_pipes(int fd_in, int fd_out);
pid_t	create_fork(t_command *cmd, int fd_in, int fd_out);

void	create_pipe(void)
{
	if (pipe(term()->pipe_fd) == -1)
	{
		term()->exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	set_pipes(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		if (fd_out != term()->pipe_fd[1])
			close(fd_out);
	}
}

pid_t	create_fork(t_command *cmd, int fd_in, int fd_out)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		set_pipes(fd_in, fd_out);
		if (is_builtin(cmd->name))
			execute_builtin(cmd);
		else
			execute_red(cmd);
		exit(0);
	}
	else
	{
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO && fd_out != term()->pipe_fd[1])
			close(fd_out);
	}
	return (child_pid);
}
