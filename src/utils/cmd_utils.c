/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:44:26 by anlima            #+#    #+#             */
/*   Updated: 2023/09/21 14:53:25 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify_cmd(char *cmd);

int	verify_cmd(char *cmd)
{
	if (((ft_strncmp(cmd, "exit", 4) == 0) && (cmd[4] == ' ' || cmd[4] == '\0')) ||
		((ft_strncmp(cmd, "echo", 4) == 0) && (cmd[4] == ' ' || cmd[4] == '\0')) ||
		((ft_strncmp(cmd, "cd", 2) == 0) && (cmd[2] == ' ' || cmd[2] == '\0')) ||
		((ft_strncmp(cmd, "clear", 5) == 0) && (cmd[5] == ' ' || cmd[5] == '\0')) ||
		((ft_strncmp(cmd, "pwd", 3) == 0) && (cmd[3] == ' ' || cmd[3] == '\0')) ||
		((ft_strncmp(cmd, "env", 3) == 0) && (cmd[3] == ' ' || cmd[3] == '\0')) ||
		((ft_strncmp(cmd, "unset", 5) == 0) && (cmd[5] == ' ' || cmd[5] == '\0')) ||
		((ft_strncmp(cmd, "export", 6) == 0) && (cmd[6] == ' ' || cmd[6] == '\0')))
			return (1);
	return (0);
}
