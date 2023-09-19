/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:49:20 by anlima            #+#    #+#             */
/*   Updated: 2023/09/19 23:50:02 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_term	*term(void);
void	set_env(char **input);

t_term	*term(void)
{
	static t_term	term;

	return (&term);
}

void	set_env(char **input)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (input[i] != NULL)
		i++;
	term()->env = malloc(sizeof(char *) * (i + 1));
	while (++j < i)
		term()->env[j] = ft_strdup(input[j]);
	term()->env[j] = NULL;
}
