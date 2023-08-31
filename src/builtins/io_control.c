/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/08/31 16:37:49 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_exit(void);
void	execute_echo(void);
void	execute_clear(void);
void	execute_ls(char *str);

void	execute_ls(char *str)
{
	pid_t	id;
	char	**args;

	// throw 127 error when command is not found
	id = fork();
	if (id == 0)
	{
		if (str[3] && str[2] == ' ' && str[3] == '-')
			args = ft_split(ft_strjoin("/bin/ls ",
						&str[3]), ' ');
		else if (str[2] == '\0')
			args = ft_split(ft_strjoin("/bin/ls ",
						&str[2]), ' ');
		execve(args[0], args, NULL);
	}
}

void	execute_echo(void)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (term()->cmd_table[++i])
	{
		if (term()->cmd_table[i][0] == '"')
			j++;
	}
	i = 0;
	while (term()->cmd_table[++i])
		printf("%s%s%s ", BLUE, term()->cmd_table[i], CLEAR);
	printf("\n");
}

void	execute_clear(void)
{
	printf("\033c");
}
