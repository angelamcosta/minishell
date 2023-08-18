/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/08/18 16:47:24 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_cd(void);
void	execute_pwd(void);

void	execute_pwd(void)
{
	char			*path;

	path = getcwd(NULL, 0);
	if (path)
		printf("%s%s%s\n", BLUE, path, CLEAR);
	else
		perror("pwd");
	free(path);
}

void	execute_cd(void)
{
	if (term()->arguments[1] == NULL)
	{
		if (term()->home == NULL)
			return (perror("cd"));
		if (chdir(term()->home) != 0)
			return (perror("cd"));
	}
	else
	{
		if (chdir(term()->arguments[1]) != 0)
			return (perror("cd"));
	}
}
