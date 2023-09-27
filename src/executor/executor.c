/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/09/27 23:13:36 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);
void	execute_command(t_command *cmd);
void	execute_no_red(t_command *cmd, char *path);
void	execute_in(t_command *cmd, char *filename, char *path);
void	execute_out(t_command *cmd, char *filename, char *path);

void	executor(void)
{
	int	i;

	i = -1;
	while (term()->cmd_list[++i].name)
	{
		if (ft_strncmp(term()->cmd_list[i].name, "exit", 5) == 0)
			execute_exit();
		else if (ft_strncmp(term()->cmd_list[i].name, "echo", 5) == 0)
			execute_echo(term()->cmd_list[i].args);
		else if (ft_strncmp(term()->cmd_list[i].name, "cd", 3) == 0)
			execute_cd(term()->cmd_list[i].args);
		else if (ft_strncmp(term()->cmd_list[i].name, "pwd", 4) == 0)
			execute_pwd(term()->cmd_list[i].args);
		else if (ft_strncmp(term()->cmd_list[i].name, "env", 4) == 0)
			execute_env(term()->cmd_list[i].args);
		else if (ft_strncmp(term()->cmd_list[i].name, "export", 7) == 0)
			execute_export(term()->cmd_list[i].args);
		else if (ft_strncmp(term()->cmd_list[i].name, "unset", 6) == 0)
			execute_unset(term()->cmd_list[i].args);
		else if (ft_strncmp(term()->cmd_list[i].name, "clear", 6) == 0)
			execute_clear();
		else
			execute_command(&term()->cmd_list[i]);
	}
}

void	execute_command(t_command *cmd)
{
	int		i;
	char	*path;
	char	**in_red;
	char	**out_red;

	path = get_path(cmd->name);
	if (cmd->in_red[0] != NULL || cmd->out_red[0] != NULL)
	{
		out_red = cmd->out_red;
		in_red = cmd->in_red;
		i = -1;
		term()->in_cmd = 1;
		while (cmd->in_red[++i])
		{
			if (!cmd->in_red[i + 1])
				execute_in(cmd, cmd->in_red[i], path);
		}
		i = -1;
		while (cmd->out_red[++i])
			execute_out(cmd, cmd->out_red[i], path);
		term()->in_cmd = 0;
	}
	else
		execute_no_red(cmd, path);
}

void	execute_no_red(t_command *cmd, char *path)
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
		execve(path, cmd->args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(child_pid, NULL, 0);
}

void	execute_in(t_command *cmd, char *filename, char *path)
{
	int		in;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		in = open(filename, O_RDONLY);
		if (in == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(in, STDIN_FILENO);
		close(in);
		execve(path, cmd->args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(child_pid, NULL, 0);
}

void	execute_out(t_command *cmd, char *filename, char *path)
{
	int		out;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (out == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(out, STDOUT_FILENO);
		close(out);
		execve(path, cmd->args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(child_pid, NULL, 0);
}
