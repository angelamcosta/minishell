/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/09/21 15:43:32 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cd(char *str);
void	execute_pwd(char *str);

void	execute_cd(char *str)
{
	char	**input;

	input = ft_split(str, ' ');
	if (input[1] == NULL)
	{
		if (term()->home == NULL)
			return (perror("cd"));
		if (chdir(term()->home) != 0)
			return (perror("cd"));
	}
	else
	{
		if (chdir(input[1]) != 0)
			return (perror("cd"));
	}
}

void	execute_pwd(char *str)
{
	char	*path;
	char	**input;

	input = ft_split(str, ' ');
	if (input[1] != NULL)
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
