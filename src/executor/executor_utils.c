/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:06:45 by anlima            #+#    #+#             */
/*   Updated: 2023/09/28 18:30:46 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		is_builtin(char *cmd_name);
void	execute_builtin(t_command *cmd);

void	execute_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->name, "exit", 5) == 0)
		execute_exit();
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
		execute_echo(&cmd->args[1]);
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
}

int	is_builtin(char *cmd_name)
{
	if ((ft_strncmp(cmd_name, "exit", 5) == 0)
		|| (ft_strncmp(cmd_name, "echo", 5) == 0)
		|| (ft_strncmp(cmd_name, "cd", 3) == 0)
		|| (ft_strncmp(cmd_name, "pwd", 4) == 0)
		|| (ft_strncmp(cmd_name, "env", 4) == 0)
		|| (ft_strncmp(cmd_name, "export", 7) == 0)
		|| (ft_strncmp(cmd_name, "unset", 6) == 0)
		|| (ft_strncmp(cmd_name, "clear", 6) == 0))
		return (1);
	return (0);
}
