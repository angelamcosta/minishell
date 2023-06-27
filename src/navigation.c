/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:34 by anlima            #+#    #+#             */
/*   Updated: 2023/06/27 23:35:43 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_cd(void);
void	execute_pwd(void);

void	execute_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
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
