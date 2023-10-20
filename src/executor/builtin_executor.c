/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:35:02 by anlima            #+#    #+#             */
/*   Updated: 2023/10/20 14:50:50 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);
void	restore_io(t_command *cmd);
void	redirect_io(t_command *cmd);
void	execute_builtin(t_command *cmd);

void	executor(void)
{
	if (!term()->cmd_list->next && is_builtin(term()->cmd_list->name))
	{
		execute_builtin(&term()->cmd_list[0]);
		return ;
	}
	if (!term()->cmd_list->pipe_output && !term()->cmd_list->prev)
	{
		redirect_io(&term()->cmd_list[0]);
		restore_io(&term()->cmd_list[0]);
	}
	create_fork();
}

void	execute_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->name, "$?", 2) == 0)
		printf("%i\n", g_exit);
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
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

void	redirect_io(t_command *cmd)
{
	cmd->stdin_backup = dup(STDIN_FILENO);
	if (cmd->stdin_backup == -1)
		perror("dup2 stdin backup");
	cmd->stdout_backup = dup(STDOUT_FILENO);
	if (cmd->stdout_backup == -1)
		perror("dup2 stdout backup");
	if (cmd->fd_in != -1)
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2 fd_in");
	if (cmd->fd_out != -1)
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 fd_out");
}

void	restore_io(t_command *cmd)
{
	if (cmd->stdin_backup != -1)
	{
		if (dup2(cmd->stdin_backup, STDIN_FILENO) == -1)
			perror("dup2 error");
		close(cmd->stdin_backup);
		cmd->stdin_backup = -1;
	}
	if (cmd->stdout_backup != -1)
	{
		if (dup2(cmd->stdout_backup, STDOUT_FILENO) == -1)
			perror("dup2 error");
		close(cmd->stdout_backup);
		cmd->stdout_backup = -1;
	}
}
