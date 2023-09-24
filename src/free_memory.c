/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:52:58 by anlima            #+#    #+#             */
/*   Updated: 2023/09/24 19:45:03 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(void);
void	clean_mallocs(void);
void	free_commands(void);

void	clean_mallocs(void)
{
	free_tokens();
	free_commands();
	free(term()->command);
	term()->command = NULL;
}

void	free_tokens(void)
{
	int	i;

	if (term()->tokens)
	{
		i = -1;
		while (term()->tokens[++i] != NULL)
		{
			free(term()->tokens[i]->value);
			free(term()->tokens[i]);
		}
		free(term()->tokens);
		term()->tokens = NULL;
	}
}

void	free_commands(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MAX_TOKENS && term()->cmd_list[i].name != NULL)
	{
		free(term()->cmd_list[i].name);
		j = -1;
		while (term()->cmd_list[i].args[++j] != NULL)
			free(term()->cmd_list[i].args[j]);
		j = -1;
		while (term()->cmd_list[i].in_red[++j] != NULL)
			free(term()->cmd_list[i].in_red[j]);
		j = -1;
		while (term()->cmd_list[i].out_red[++j] != NULL)
			free(term()->cmd_list[i].out_red[j]);
		j = -1;
		while (term()->cmd_list[i].delimiters[++j] != NULL)
			free(term()->cmd_list[i].delimiters[j]);
	}
	ft_memset(term()->cmd_list, 0, sizeof(term()->cmd_list));
}
