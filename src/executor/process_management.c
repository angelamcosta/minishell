/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:42 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 15:38:01 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fds(t_command *cmd);
pid_t	create_fork(t_command *cmd, int i);
void	treat_child(t_command *cmd, int i);

pid_t	create_fork(t_command *cmd, int i)
{
	pid_t	child_pid;

	signal(SIGINT, SIG_IGN);
	if (pipe(cmd->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		treat_child(cmd, i);
	else
		close_fds(cmd);
	return (child_pid);
}

void	treat_child(t_command *cmd, int i)
{
	char	*path;

	signals_child();
	if (term()->prev_fd[0] != -1)
	{
		dup2(term()->prev_fd[0], STDIN_FILENO);
		close(term()->prev_fd[0]);
		close(term()->prev_fd[1]);
	}
	else
		dup2(term()->stdin_copy, STDIN_FILENO);
	close(cmd->fd[0]);
	if ((i + 1) < term()->count_cmd)
		dup2(cmd->fd[1], STDOUT_FILENO);
	else
		dup2(term()->stdout_copy, STDOUT_FILENO);
	path = execute_red(cmd);
	if (cmd->name && !is_builtin(cmd->name))
		execute_command(cmd, path);
	else
		execute_builtin(cmd);
	exit(g_exit);
}

void	close_fds(t_command *cmd)
{
	if (term()->prev_fd[0] != -1)
	{
		close(term()->prev_fd[0]);
		close(term()->prev_fd[1]);
	}
	term()->prev_fd[0] = cmd->fd[0];
	term()->prev_fd[1] = cmd->fd[1];
}
