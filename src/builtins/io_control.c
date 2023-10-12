/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/10/12 14:23:12 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_exit(void);
void	execute_clear(void);
void	print_str(char *str);
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
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = check_flag(args[0]);
	if (flag)
		i++;
	while (args && args[i])
	{
		if ((i > 0 && !flag) || i > 1 && flag)
			write(1, " ", 1);
		print_str(args[i]);
		i++;
	}
}

void	print_str(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str && str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			write(1, &str[i], 1);
		else
		{
			if (quote == 0)
				quote = str[i];
			else if (str[i] == quote)
				quote = 0;
			else if (quote != str[i])
				write(1, &str[i], 1);
		}
	}
}
