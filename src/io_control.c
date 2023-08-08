/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:16:11 by anlima            #+#    #+#             */
/*   Updated: 2023/08/08 15:49:01 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_ls(void);
void	execute_exit(void);
void	execute_echo(void);
void	execute_clear(void);

void	execute_ls(void)
{
	DIR				*dir;
	char			*path;
	struct dirent	*ent;

	path = getcwd(NULL, 0);
	dir = opendir(path);
	if (dir)
	{
		ent = readdir(dir);
		while (ent)
		{
			if (ent->d_name[0] != '.')
				printf("%s ", ent->d_name);
			ent = readdir(dir);
		}
		printf("\n");
		closedir(dir);
	}
	else
		perror("ls");
	free(path);
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
		printf("%s ", term()->arguments[i]);
	printf("\n");
}

void	execute_clear(void)
{
	printf("\033c");
}
