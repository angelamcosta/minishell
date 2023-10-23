/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:30:40 by anlima            #+#    #+#             */
/*   Updated: 2023/10/23 23:37:08 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_red(t_command *cmd, char *str);
int	is_out_red(t_command *cmd, char *str);
int	is_append(t_command *cmd, char *str);

int	is_in_red(t_command *cmd, char *str)
{
	int	i;

	i = -1;
	while (cmd->in_red[++i])
	{
		if (ft_strncmp(cmd->in_red[i], str, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}

int	is_out_red(t_command *cmd, char *str)
{
	int	i;

	i = -1;
	while (cmd->out_red[++i])
	{
		if (ft_strncmp(cmd->out_red[i], str, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}

int	is_append(t_command *cmd, char *str)
{
	int	i;

	i = -1;
	while (cmd->append[++i])
	{
		if (ft_strncmp(cmd->append[i], str, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}
