/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:52:47 by anlima            #+#    #+#             */
/*   Updated: 2023/10/17 17:57:38 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	can_fork(t_command *cmd);
int	treat_exit_arg(char *str);
int	is_valid_varname(char *str);

int	is_valid_varname(char *str)
{
	int	i;

	i = -1;
	if (!str || *str == '\0')
		return (0);
	while (str[++i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
	}
	return (1);
}

int	can_fork(t_command *cmd)
{
	if (!cmd->name && cmd->args[0] && ft_isdigit(*cmd->args[0]))
	{
		print_str(cmd->args[0]);
		write(1, "\n", 1);
		return (0);
	}
	else if (cmd->name && ((ft_strncmp(cmd->name, "exit", 5) == 0)
			|| (ft_strncmp(cmd->name, "cd", 3) == 0) || (ft_strncmp(cmd->name,
					"env", 4) == 0) || (ft_strncmp(cmd->name, "unset", 6) == 0)
			|| (ft_strncmp(cmd->name, "export", 7) == 0)))
		return (0);
	return (1);
}

int	treat_exit_arg(char *str)
{
	int	i;
	int	nb;
	int	flag;

	i = 0;
	nb = 0;
	flag = 0;
	while (str[i] == '"' || str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag = 1;
		i++;
	}
	nb = ft_atoi(&str[i]);
	if (flag)
		nb *= -1;
	return (nb);
}
