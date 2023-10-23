/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:31:26 by anlima            #+#    #+#             */
/*   Updated: 2023/10/23 23:46:53 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		find_len(char *value);
int		count_pipes(char *input);
char	*dup_quoted(char *value);

int	count_pipes(char *input)
{
	int	i;
	int	count;
	int	quote;

	i = -1;
	quote = 0;
	count = 0;
	while (input[++i])
	{
		while (input[i] == ' ' && quote == 0)
			i++;
		if (input[i] == '"' || input[i] == '\'')
			change_quote(&quote, input[i]);
		if ((input[i] == '|') && quote == 0)
			count++;
	}
	term()->count_cmd = count + 1;
	return (count);
}

char	*dup_quoted(char *value)
{
	char	*start;
	char	*end;
	char	*result;
	char	*dest;
	int		total_len;

	total_len = find_len(value);
	if (total_len == (int)ft_strlen(value))
		return (ft_strdup(value));
	result = (char *)malloc(total_len + 1);
	start = value;
	dest = result;
	while (*start)
	{
		if (*start == '"')
		{
			end = ft_strchr(start + 1, '"');
			if (!end)
				break ;
			ft_strlcpy(dest, start + 1, end - start + 1);
			dest += (end - start - 1);
			start = end + 1;
		}
		else
		{
			*dest = *start;
			dest++;
			start++;
		}
	}
	*dest = '\0';
	return (result);
}

int	find_len(char *value)
{
	char	*end;
	char	*start;
	int		total_len;

	start = value;
	total_len = 0;
	while (*start)
	{
		if (*start == '"')
		{
			end = ft_strchr(start + 1, '"');
			if (!end)
				break ;
			total_len += (end - start - 1);
			start = end + 1;
		}
		else
		{
			total_len++;
			start++;
		}
	}
	return (total_len);
}
