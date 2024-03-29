/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:34:11 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 15:38:37 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_flag(char *input);
int	is_builtin(char *cmd_name);

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
