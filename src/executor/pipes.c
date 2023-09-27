/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:13:49 by anlima            #+#    #+#             */
/*   Updated: 2023/09/27 18:26:33 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_pipe(void);
char	*get_path(char *cmd_name);

void	create_pipe(void)
{
	if (pipe(term()->pipe_fd) == -1)
	{
		term()->exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

char	*get_path(char *cmd_name)
{
	int		i;
	char	*path;
	char	*test_path;
	char	**paths;

	i = 0;
	while (ft_strncmp(term()->env[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(term()->env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		test_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(test_path, cmd_name);
		free(test_path);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (path);
}
