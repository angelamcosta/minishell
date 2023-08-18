/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:42 by anlima            #+#    #+#             */
/*   Updated: 2023/08/18 16:48:52 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_env(void);
void	execute_unset(void);
void	execute_export(void);

void	execute_env(void)
{
	int	i;

	i = -1;
	while (term()->env && term()->env[++i])
		printf("%s%s%s\n", BLUE, term()->env[i], CLEAR);
}

void	execute_export(void)
{
	char	**env_ptr;

	env_ptr = environ;
	putenv(term()->arguments[1]);
}
