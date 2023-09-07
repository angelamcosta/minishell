/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/09/07 17:25:03 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(void)
{
	int	i;

	i = -1;
	while (term()->cmd_table[++i])
	{
		if (ft_strncmp(term()->cmd_table[i], "ls", 2) == 0)
			execute_ls(term()->cmd_table[i]);
		else if (ft_strncmp(term()->cmd_table[i], "clear", 6) == 0)
			execute_clear();
		else if (ft_strncmp(term()->cmd_table[i], "exit", 5) == 0)
			execute_exit();
		else if (ft_strncmp(term()->cmd_table[i], "echo", 4) == 0)
			execute_echo(term()->cmd_table[i]);
	}
}
