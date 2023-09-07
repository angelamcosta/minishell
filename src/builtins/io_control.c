/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/09/07 17:46:57 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_exit(void);
void	execute_clear(void);
void	execute_ls(char *str);
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

void	execute_ls(char *str)
{
	pid_t	id;
	char	**args;

	id = fork();
	if (id == 0)
	{
		if (str[3] && str[2] == ' ' && str[3] == '-')
			args = ft_split(ft_strjoin("/bin/ls ", &str[3]), ' ');
		else if (str[2] == '\0')
			args = ft_split(ft_strjoin("/bin/ls ", &str[2]), ' ');
		execve(args[0], args, NULL);
		perror("execve");
		exit(1);
	}
	else if (id < 0)
		perror("fork");
	wait(&id);
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
