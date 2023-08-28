/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:58 by anlima            #+#    #+#             */
/*   Updated: 2023/08/28 15:59:13 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_mallocs(void)
{
	int	i;

	i = -1;
	while (term()->arguments && term()->arguments[++i])
	{
		if (term()->arguments[i])
			free(term()->arguments[i]);
	}
	free(term()->arguments);
	free(term()->command);
}
