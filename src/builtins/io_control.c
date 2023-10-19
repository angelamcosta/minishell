/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/10/19 21:54:17 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_clear(void);
void	print_str(char *str);
int		is_numeric(char *arg);
void	execute_echo(char **args);
void	execute_exit(char **args);

void	execute_exit(char **args)
{
	add_history(term()->command);
	if (args[1] && args[1] != NULL)
		g_exit = EXIT_FAILURE;
	else if (args[0] && !is_numeric(args[0]))
		g_exit = 2;
	else if (args[0] && is_numeric(args[0]))
	{
		g_exit = treat_exit_arg(args[0]);
		if (g_exit < 0)
			g_exit = (g_exit + 256);
		g_exit = g_exit % 256;
	}
	print_str("exit\n");
	clean_mallocs();
	free_env();
	exit(g_exit);
}

void	execute_clear(void)
{
	printf("\033c");
	g_exit = EXIT_SUCCESS;
}

void	execute_echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = check_flag(args[0]);
	if (flag)
		i++;
	while (args && args[i])
	{
		if ((i > 0 && !flag) || (i > 1 && flag))
			write(1, " ", 1);
		print_str(args[i]);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	g_exit = EXIT_SUCCESS;
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

int	is_numeric(char *arg)
{
	int	i;
	int	f_plus;
	int	f_minus;

	f_plus = 0;
	f_minus = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '-')
		{
			if (f_minus)
				return (0);
			f_minus = 1;
		}
		if (arg[i] == '+')
		{
			if (f_plus)
				return (0);
			f_plus = 1;
		}
		if (ft_isalpha(arg[i]))
			return (0);
	}
	return (1);
}
