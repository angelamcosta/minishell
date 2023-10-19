/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:31:26 by anlima            #+#    #+#             */
/*   Updated: 2023/10/19 22:53:06 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int		len;
	char	*end;
	char	*start;
	char	*result;

	start = ft_strchr(value, '"');
	if (start == NULL)
		return (ft_strdup(value));
	end = ft_strchr(value + 1, '"');
	len = end - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(result, start + 1, len);
	return (result);
}
