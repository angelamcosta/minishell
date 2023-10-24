/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:28:37 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 15:21:41 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*aux_split(char *input, int i);
void	should_add(char *input, int i, char **strs, int *k);

char	*aux_split(char *input, int i)
{
	char	*subs;
	char	*temp;
	char	*result;

	temp = NULL;
	result = NULL;
	subs = ft_substr(input, 0, i);
	if (subs && ft_strlen(subs) > 0)
	{
		if (should_expand(subs))
		{
			temp = expand_var(subs);
			if (temp != NULL)
				result = ft_strdup(temp);
		}
		else
			result = ft_strdup(subs);
	}
	free(subs);
	free(temp);
	if (result)
		return (result);
	return (NULL);
}

void	should_add(char *input, int i, char **strs, int *k)
{
	char	*temp;

	temp = aux_split(input, i);
	if (temp != NULL)
		strs[++(*k)] = ft_strdup(temp);
	free(temp);
}
