/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 15:38:20 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *cmd_name);
void	execute_command(t_command *cmd, char *path);

char	*get_path(char *cmd_name)
{
	int		i;
	char	*path;
	char	*test_path;
	char	**paths;

	paths = ft_split(getenv("PATH") + 5, ':');
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
	if (!path)
		return (NULL);
	return (path);
}

void	execute_command(t_command *cmd, char *path)
{
	if (!cmd->name)
		exit(EXIT_SUCCESS);
	if (access(path, X_OK) == -1)
	{
		fprintf(stderr, "%s: command not found\n", cmd->name);
		exit(NOT_FOUND);
	}
	execve(path, cmd->args, NULL);
	set_signals();
	perror("execve");
	exit(EXIT_FAILURE);
}
