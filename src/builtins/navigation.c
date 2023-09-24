/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/09/24 21:31:31 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cd(char **args);
void	execute_pwd(char **args);

// TODO: - deal with multiple args in cd
void	execute_cd(char **args)
{
	if (args[0] == NULL || ft_strncmp(args[0], "~", 2) == 0)
	{
		if (term()->home == NULL)
			return (perror("cd"));
		if (chdir(term()->home) != 0)
			return (perror("cd"));
	}
	else
	{
		if (chdir(args[0]) != 0)
			return (perror("cd"));
	}
}

void	execute_pwd(char **args)
{
	char	*path;

	if (args[0] != NULL)
	{
		printf("%spwd: too many arguments%s\n", RED, CLEAR);
		return ;
	}
	path = getcwd(NULL, 0);
	if (path)
		printf("%s%s%s\n", BLUE, path, CLEAR);
	else
		perror("pwd");
	free(path);
}
