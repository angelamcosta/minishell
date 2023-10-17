/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/10/17 14:34:50 by anlima           ###   ########.fr       */
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
			print_str("cd: No such file or directory\n");
		}
		else
			g_exit = EXIT_SUCCESS;
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			g_exit = EXIT_FAILURE;
			print_str("cd: No such file or directory\n");
		}
		else
			g_exit = EXIT_SUCCESS;
	}
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
