/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:58 by anlima            #+#    #+#             */
/*   Updated: 2023/09/18 14:10:57 by anlima           ###   ########.fr       */
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
	{
		free(term()->command);
		term()->command = NULL;
	}
}
