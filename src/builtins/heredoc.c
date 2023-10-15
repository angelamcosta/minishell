/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:58:32 by anlima            #+#    #+#             */
/*   Updated: 2023/10/15 13:48:05 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredocs(void);
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

void	handle_heredocs(void)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < term()->count_cmd)
	{
		while (term()->cmd_list[i].delimiters[++j])
			heredoc(term()->cmd_list[i].delimiters[j]);
	}
}
