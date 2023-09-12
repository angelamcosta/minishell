/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/09/12 16:10:56 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_exit(void);
void	execute_clear(void);
void	execute_echo(char *token);

void	execute_exit(void)
{
	add_history(term()->command);
	clean_mallocs();
	exit(1);
}

void	execute_clear(void)
{
	printf("\033c");
}

void	execute_echo(char *str)
{
	int		i;
	char	quote;

	i = 4;
	while (str[i])
	{
		while (str[++i] && str[i] != '"' && str[i] != '\'')
			write(1, &str[i], 1);
		if (str[i])
			quote = str[i];
		else
			break ;
		while (str[++i] && str[i] != quote)
			write(1, &str[i], 1);
	}
	printf("\n");
}
