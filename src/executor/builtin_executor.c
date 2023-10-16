/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:35:02 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 19:57:56 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);
void	execute_builtin(t_command *cmd);
void	handle_commands(int i, int fd_out, int *fd_in, pid_t *child_pids);

void	executor(void)
{
	int		i;
	int		fd_in;
	int		fd_out;
	int		status;
	pid_t	*child_pids;

	handle_heredocs();
	fd_in = STDIN_FILENO;
	fd_out = dup(STDOUT_FILENO);
	child_pids = malloc(term()->count_cmd * sizeof(pid_t));
	i = -1;
	while (++i < term()->count_cmd)
		handle_commands(i, fd_out, &fd_in, child_pids);
	i = -1;
	while (++i < term()->count_cmd)
	{
		if (child_pids[i] > 0)
			wait(&status);
	}
	term()->exit_status = 0;
	free(child_pids);
}

void	execute_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->name, "$?", 2) == 0)
	{
		printf("%i\n", term()->exit_status);
		return ;
	}
	if (ft_strncmp(cmd->name, "exit", 5) == 0)
		execute_exit(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
	{
		execute_echo(&cmd->args[1]);
		if (check_flag(cmd->args[1]) && cmd->args[2])
			write(1, "\e[38;5;0;48;5;255m%\e[0m\n", 24);
	}
	else if (ft_strncmp(cmd->name, "cd", 3) == 0)
		execute_cd(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		execute_pwd();
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		execute_env(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		execute_export(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		execute_unset(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "clear", 6) == 0)
		execute_clear();
}

void	handle_commands(int i, int fd_out, int *fd_in, pid_t *child_pids)
{
	if (i == term()->count_cmd - 1 && (is_builtin(term()->cmd_list[i].name)))
	{
		execute_red(&term()->cmd_list[i]);
		execute_builtin(&term()->cmd_list[i]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		return ;
	}
	else if (i < term()->count_cmd - 1)
	{
		create_pipe();
		child_pids[i] = create_fork(&term()->cmd_list[i], *fd_in,
				term()->pipe_fd[1]);
		close(term()->pipe_fd[1]);
		*fd_in = term()->pipe_fd[0];
	}
	else
	{
		child_pids[i] = create_fork(&term()->cmd_list[i], *fd_in,
				STDOUT_FILENO);
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
	}
}
