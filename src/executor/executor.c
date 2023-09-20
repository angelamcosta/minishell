/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/09/20 23:06:55 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);

void	executor(void)
{
	int	i;

	i = -1;
	while (term()->cmd_table[++i])
	{
		if (ft_strncmp(term()->cmd_table[i], "exit", 4) == 0)
			execute_exit();
		else if (ft_strncmp(term()->cmd_table[i], "echo", 4) == 0)
			execute_echo(term()->cmd_table[i]);
		else if (ft_strncmp(term()->cmd_table[i], "cd", 2) == 0)
			execute_cd(term()->cmd_table[i]);
		else if (ft_strncmp(term()->cmd_table[i], "clear", 5) == 0)
			execute_clear();
		else if (ft_strncmp(term()->cmd_table[i], "pwd", 3) == 0)
			execute_pwd(term()->cmd_table[i]);
		else if (ft_strncmp(term()->cmd_table[i], "env", 3) == 0)
			execute_env(term()->cmd_table[i]);
		else if (ft_strncmp(term()->cmd_table[i], "unset", 5) == 0)
			execute_unset(term()->cmd_table[i]);
		else if (ft_strncmp(term()->cmd_table[i], "export", 6) == 0)
			execute_export(term()->cmd_table[i]);
	}
}
