/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:58:32 by anlima            #+#    #+#             */
/*   Updated: 2023/10/03 16:01:56 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc(char *delimiter);

void	heredoc(char *delimiter)
{
	int		fd;
	int		bytes_read;
	char	line[1024];

	fd = open("temp_here.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
	while (1)
	{
		bytes_read = read(STDIN_FILENO, &line, BUFF_SIZE);
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			break ;
		write(fd, line, bytes_read);
	}
}
