/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/09/25 18:37:31 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);
void	execute_cmd(t_command *cmd);
void	execute(t_command *cmd, char *in, char *out, char *path);

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
			execute_cmd(&term()->cmd_list[i]);
	}
}

void	execute_cmd(t_command *cmd)
{
	int		i;
	char	*path;

	path = get_path(cmd->name);
	if (path == NULL)
	{
		printf("Command not found: %s\n", cmd->name);
		term()->exit_status = NOT_FOUND;
		return ;
	}
	if (cmd->in_red && cmd->in_red[0] != NULL)
	{
		i = -1;
		while (cmd->in_red[++i])
			execute(cmd, cmd->in_red[i], 0, path);
	}
	if (cmd->out_red && cmd->out_red[0] != NULL)
	{
		i = -1;
		while (cmd->out_red[++i])
			execute(cmd, 0, cmd->out_red[i], path);
	}
	else
		execute(cmd, 0, 0, path);
	free(path);
}

void	execute(t_command *cmd, char *in, char *out, char *path)
{
	pid_t	child_pid;

	create_pipe();
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (in != NULL)
			redirect_stdin(in);
		if (out != NULL)
			redirect_stdout(out);
		close(term()->pipe_fd[1]);
		execve(path, cmd->args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(child_pid, NULL, 0);
}
