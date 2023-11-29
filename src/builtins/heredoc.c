/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:58:32 by anlima            #+#    #+#             */
/*   Updated: 2023/10/25 15:08:31 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredocs(void);
void	heredoc(char *delimiter);

void	heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	fd = open("temp_here.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			write(0, "heredoc delimited by eof\n", 26);
			break ;
		}
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
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
	set_signals();
}
