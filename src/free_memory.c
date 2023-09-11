/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:58 by anlima            #+#    #+#             */
/*   Updated: 2023/09/11 17:16:52 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_mallocs(void)
{
	int	i;

	i = -1;
	if (term()->cmd_table)
	{
		while (term()->cmd_table[++i])
		{
			if (term()->cmd_table[i])
				free(term()->cmd_table[i]);
		}
		free(term()->cmd_table);
		term()->cmd_table = NULL;
	}
	if (term()->command)
		free(term()->command);
	free_commands(term()->command_tree);
	term()->command_tree = NULL;
}
