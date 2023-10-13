/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/10/13 14:27:59 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cd(char **args);
void	execute_pwd(char **args);

void	execute_cd(char **args)
{
	if (args[1] == NULL || ft_strncmp(args[1], "~", 2) == 0)
	{
		if (term()->home == NULL)
			return (perror("cd"));
		if (chdir(term()->home) != 0)
			return (perror("cd"));
	}
	else
	{
		if (chdir(args[1]) != 0)
			return (perror("cd"));
	}
}

void	execute_pwd(char **args)
{
	char	*path;

	if (args[1] != NULL)
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
