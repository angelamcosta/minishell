/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:58 by anlima            #+#    #+#             */
/*   Updated: 2023/08/31 15:45:15 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_mallocs(void)
{
	int	i;

	i = -1;
	while (term()->cmd_table && term()->cmd_table[++i])
	{
		if (term()->cmd_table[i])
			free(term()->cmd_table[i]);
	}
	free(term()->cmd_table);
	free(term()->command);
}
