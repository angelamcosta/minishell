/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:13:49 by anlima            #+#    #+#             */
/*   Updated: 2023/09/25 18:33:58 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_pipe(void);
char	*get_path(char *cmd_name);
void	redirect_stdin(char *filename);
void	redirect_stdout(char *filename);
void	wait_child_proc(pid_t child_pid);

void	create_pipe(void)
{
	if (pipe(term()->pipe_fd) == -1)
	{
		term()->exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	redirect_stdout(char *filename)
{
	int		out;

	out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(out);
}

void	redirect_stdin(char *filename)
{
	int		in;

	in = open(filename, O_RDONLY, 0777);
	if (in == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(in);
}

void	wait_child_proc(pid_t child_pid)
{
	int	status;

	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		term()->exit_status = status;
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
