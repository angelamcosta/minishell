/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/09/24 21:25:42 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_exit(void);
void	execute_clear(void);
void	execute_echo(char **args);

void	execute_exit(void)
{
	add_history(term()->command);
	clean_mallocs();
	free_env();
	printf("exit\n");
	exit(term()->exit_status);
}

void	execute_clear(void)
{
	printf("\033c");
}

void	execute_echo(char **args)
{
	int		i;
	int		j;
	char	quote;
	char	*str;

	i = -1;
	while (args && args[++i])
	{
		j = -1;
		quote = 0;
		str = args[i];
		while (str && str[++j])
		{
			while (str[j] && (str[j] != '"' && str[j] != '\''))
				write(1, &str[j++], 1);
			if (str[j] && quote == 0)
				quote = str[j++];
			while (str[j] && str[j] != quote)
				write(1, &str[j++], 1);
			if (args[i + 1])
				write(1, " ", 1);
		}
	}
	printf("\n");
}
