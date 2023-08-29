/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/08/29 16:19:48 by anlima           ###   ########.fr       */
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

	if (ft_strncmp(str, "ls", 2) == 0)
	{
		if (str[3] && str[2] == ' ' && str[3] == '-')
		{
			id = fork();
			if (id == 0)
			{
				args = ft_split(ft_strjoin("/bin/ls ",
							&str[3]), ' ');
				execve(args[0], args, NULL);
			}
		}
	}
}

void	execute_echo(void)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (term()->arguments[++i])
	{
		if (term()->arguments[i][0] == '"')
			j++;
	}
	i = 0;
	while (term()->arguments[++i])
		printf("%s%s%s ", BLUE, term()->arguments[i], CLEAR);
	printf("\n");
}

void	execute_clear(void)
{
	printf("\033c");
}
