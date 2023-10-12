/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:58:32 by anlima            #+#    #+#             */
/*   Updated: 2023/10/09 17:59:43 by anlima           ###   ########.fr       */
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
		write(1, "> ", 2);
		bytes_read = read(STDIN_FILENO, &line, BUFF_SIZE);
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			break ;
		write(fd, line, bytes_read);
	}
}
