/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:42 by anlima            #+#    #+#             */
/*   Updated: 2023/09/28 16:32:51 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_pipe(void);
char	*get_path(char *cmd_name);
void	find_command(t_command *cmd);
void	set_pipes(t_command *cmd, int fd_in, int fd_out);

void	create_pipe(void)
{
	if (pipe(term()->pipe_fd) == -1)
	{
		term()->exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

char	*get_path(char *cmd_name)
{
	int		i;
	char	*path;
	char	*test_path;
	char	**paths;

	i = 0;
	while (ft_strncmp(term()->env[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(term()->env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		test_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(test_path, cmd_name);
		free(test_path);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (path);
}

void	set_pipes(t_command *cmd, int fd_in, int fd_out)
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
		find_command(cmd);
	}
	else
		waitpid(child_pid, NULL, 0);
}

void	find_command(t_command *cmd)
{
	if (ft_strncmp(cmd->name, "exit", 5) == 0)
		execute_exit();
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
		execute_echo(cmd->args);
	else if (ft_strncmp(cmd->name, "cd", 3) == 0)
		execute_cd(cmd->args);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		execute_pwd(cmd->args);
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		execute_env(cmd->args);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		execute_export(cmd->args);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		execute_unset(cmd->args);
	else if (ft_strncmp(cmd->name, "clear", 6) == 0)
		execute_clear();
	else
		execute_red(cmd);
}
