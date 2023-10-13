/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:06:45 by anlima            #+#    #+#             */
/*   Updated: 2023/10/13 16:49:28 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fork_builtin(void);
int		check_flag(char *input);
int		is_builtin(char *cmd_name);
void	execute_builtin(t_command *cmd);

void	execute_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->name, "$?", 2) == 0)
	{
		printf("%i\n", term()->exit_status);
		return ;
	}
	if (ft_strncmp(cmd->name, "exit", 5) == 0)
		execute_exit();
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
	{
		execute_echo(&cmd->args[1]);
		if (check_flag(cmd->args[1]) && cmd->args[2])
			write(1, "\e[38;5;0;48;5;255m%\e[0m", 24);
		write(1, "\n", 1);
	}
	else if (ft_strncmp(cmd->name, "cd", 3) == 0)
		execute_cd(cmd->args);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		execute_pwd(cmd->args);
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		execute_env(cmd->args);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		execute_export(&cmd->args[1]);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		execute_unset(cmd->args);
	else if (ft_strncmp(cmd->name, "clear", 6) == 0)
		execute_clear();
	fork_builtin();
}

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if ((ft_strncmp(cmd_name, "$?", 2) == 0) || (ft_strncmp(cmd_name, "exit",
				5) == 0) || (ft_strncmp(cmd_name, "echo", 5) == 0)
		|| (ft_strncmp(cmd_name, "cd", 3) == 0) || (ft_strncmp(cmd_name, "pwd",
				4) == 0) || (ft_strncmp(cmd_name, "env", 4) == 0)
		|| (ft_strncmp(cmd_name, "export", 7) == 0) || (ft_strncmp(cmd_name,
				"unset", 6) == 0) || (ft_strncmp(cmd_name, "clear", 6) == 0))
		return (1);
	return (0);
}

int	check_flag(char *input)
{
	int	i;

	if (!input)
		return (0);
	if (input[0] != '-')
		return (0);
	i = 0;
	while (input[++i])
	{
		if (input[i] != 'n')
			return (0);
	}
	return (1);
}

void	fork_builtin(void)
{
	int		status;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		exit(term()->exit_status);
}
