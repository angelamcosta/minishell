/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:35:02 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 17:09:24 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);
void	treat_lastcmd(int i);
void	handle_commands(void);
void	execute_builtin(t_command *cmd);
void	wait_childs(pid_t *child_pids, int i);

void	executor(void)
{
	handle_heredocs();
	term()->stdin_copy = dup(STDIN_FILENO);
	term()->stdout_copy = dup(STDOUT_FILENO);
	term()->prev_fd[0] = -1;
	term()->prev_fd[1] = -1;
	handle_commands();
	if (dup2(term()->stdin_copy, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(term()->stdin_copy);
	if (dup2(term()->stdout_copy, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(term()->stdout_copy);
}

void	execute_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->name, "exit", 5) == 0)
		execute_exit(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
	{
		execute_echo(&cmd->args[1]);
		if (check_flag(cmd->args[1]) && cmd->args[2])
			write(1, "\e[38;5;0;48;5;255m%\e[0m\n", 24);
	}
	else if (ft_strncmp(cmd->name, "cd", 3) == 0)
		execute_cd(cmd->args);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		execute_pwd();
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		execute_env(&cmd->args[1], 0);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		execute_export(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		execute_unset(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "clear", 6) == 0)
		execute_clear();
}

void	handle_commands(void)
{
	int		i;
	pid_t	child_pids[MAX_TOKENS];

	i = -1;
	while (++i < term()->count_cmd)
	{
		if (i == term()->count_cmd - 1 && !can_fork(&term()->cmd_list[i]))
		{
			treat_lastcmd(i);
			child_pids[i] = -1;
		}
		else
			child_pids[i] = create_fork(&term()->cmd_list[i], i);
	}
	i = -1;
	while (++i < term()->count_cmd)
	{
		if (child_pids[i] != -1)
			wait_childs(child_pids, i);
	}
	set_signals();
}

void	treat_lastcmd(int i)
{
	close(term()->cmd_list[i].fd[1]);
	dup2(term()->cmd_list[i].fd[0], STDIN_FILENO);
	if ((i + 1) < term()->count_cmd)
	{
		dup2(term()->cmd_list[i].fd[1], STDOUT_FILENO);
		close(term()->cmd_list[i].fd[1]);
		close(term()->cmd_list[i].fd[0]);
	}
	else
		dup2(term()->stdout_copy, STDOUT_FILENO);
	execute_red(&term()->cmd_list[i]);
	execute_builtin(&term()->cmd_list[i]);
}

void	wait_childs(pid_t *child_pids, int i)
{
	int	status;

	waitpid(child_pids[i], &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
}
