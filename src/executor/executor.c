/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/09/24 21:53:39 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void);

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
	}
}
