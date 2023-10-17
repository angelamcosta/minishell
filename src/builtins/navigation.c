/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/10/17 17:51:10 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_pwd(void);
void	execute_cd(char **args);

void	execute_cd(char **args)
{
	if (args[1] == NULL || ft_strncmp(args[1], "~", 2) == 0)
	{
		if (term()->home == NULL || chdir(term()->home) != 0)
		{
			g_exit = EXIT_FAILURE;
			perror("cd: No such file or directory\n");
			return ;
		}
	}
	else
	{
		if (args[2])
		{
			g_exit = EXIT_FAILURE;
			perror("cd: too many arguments\n");
			return ;
		}
		else if (chdir(args[1]) != 0)
		{
			g_exit = EXIT_FAILURE;
			perror("cd: No such file or directory\n");
			return ;
		}
	}
	g_exit = EXIT_SUCCESS;
}

void	execute_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
		printf("%s\n", path);
	else
	{
		g_exit = EXIT_FAILURE;
		free(path);
		return (perror("pwd"));
	}
	g_exit = EXIT_SUCCESS;
	free(path);
}
