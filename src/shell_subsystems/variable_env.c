/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:42 by anlima            #+#    #+#             */
/*   Updated: 2023/08/31 15:44:02 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
