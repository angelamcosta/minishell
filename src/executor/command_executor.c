/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:46:17 by anlima            #+#    #+#             */
/*   Updated: 2023/10/20 18:32:11 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**check_path(void);
char	*get_path(char *cmd_name);
void	execute_command(t_command *cmd, char *path);

char	*get_path(char *cmd_name)
{
	int		i;
	char	*path;
	char	*test_path;
	char	**paths;

	paths = check_path();
	if (*paths == NULL)
		return (NULL);
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
	struct stat	path_stat;

	if (!cmd->name)
		exit(EXIT_SUCCESS);
	if (access(path, F_OK) == -1)
	{
		write(0, "command not found\n", 19);
		exit(NOT_FOUND);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		write(0, "is a directory\n", 16);
		exit(IS_DIRECTORY);
	}
	if (access(path, X_OK) == -1)
	{
		write(0, "permission denied\n", 19);
		exit(ERR_PERMISSION);
	}
	execve(path, cmd->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

char	**check_path(void)
{
	int		i;
	char	**paths;
	char	*path_env;

	i = -1;
	while (term()->env[++i])
	{
		if (ft_strncmp(term()->env[i], "PATH=", 5) == 0)
			path_env = term()->env[i] + 5;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}
