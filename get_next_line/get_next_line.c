/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:24:04 by anlima            #+#    #+#             */
/*   Updated: 2023/08/08 16:08:48 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_clean(char *str)
{
	int	i;
	int	j;
	int	is_nl;

	i = 0;
	j = 0;
	is_nl = 0;
	while (str[i])
	{
		if (is_nl)
			str[j++] = str[i];
		if (str[i] == '\n')
			is_nl = 1;
		str[i++] = '\0';
	}
	return (is_nl);
}

char	*get_next_line(int fd)
{
	static char	line[BUFFER_SIZE + 1];
	char		*next_line;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1 || FOPEN_MAX < fd)
		return (NULL);
	next_line = ft_strjoin(0, line);
	if (ft_clean(line) > 0)
		return (next_line);
	i = read(fd, line, BUFFER_SIZE);
	if (i < 0)
	{
		free(next_line);
		return (NULL);
	}
	while (i > 0)
	{
		next_line = ft_strjoin(next_line, line);
		if (ft_clean(line) > 0)
			break ;
		i = read(fd, line, BUFFER_SIZE);
	}
	return (next_line);
}
