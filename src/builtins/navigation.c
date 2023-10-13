/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/10/13 16:08:38 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cd(char **args);
void	execute_pwd(char **args);

void	execute_cd(char **args)
{
	if (args[1] == NULL || ft_strncmp(args[1], "~", 2) == 0)
	{
		if (term()->home == NULL || chdir(term()->home) != 0)
		{
			term()->exit_status = EXIT_FAILURE;
			return (perror("cd"));
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			term()->exit_status = EXIT_FAILURE;
			return (perror("cd"));
		}
	}
}

void	execute_pwd(char **args)
{
	char	*path;

	if (args[1] != NULL)
	{
		printf("%spwd: too many arguments%s\n", RED, CLEAR);
		term()->exit_status = EXIT_FAILURE;
		return ;
	}
	path = getcwd(NULL, 0);
	if (path)
		printf("%s%s%s\n", BLUE, path, CLEAR);
	else
	{
		term()->exit_status = EXIT_FAILURE;
		free(path);
		return (perror("pwd"));
	}
	free(path);
}
