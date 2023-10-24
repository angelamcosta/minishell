/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:21:57 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 15:46:58 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modify_result(char **result, char *replacement);
void	get_result(char **result, char *value, int i, int *j);
void	treat_expasion(int i, int *j, char **result, char *value);

void	treat_expasion(int i, int *j, char **result, char *value)
{
	char	*var_name;
	char	*replacement;

	replacement = NULL;
	get_result(result, value, i, j);
	*j = i;
	if (ft_strncmp(&value[i], "$?", 2) == 0)
	{
		replacement = ft_itoa(g_exit);
		(*j) += 2;
	}
	else
	{
		var_name = extract_varname(&value[i]);
		replacement = handle_variables(var_name);
		free(var_name);
		while (value[++(*j)])
		{
			if (value[(*j)] == ' ' || !ft_isalnum(value[(*j)]))
				break ;
		}
	}
	modify_result(result, replacement);
	free(replacement);
}

void	get_result(char **result, char *value, int i, int *j)
{
	char	*temp;

	temp = NULL;
	if (i - *j > 0)
	{
		if (*result)
		{
			temp = ft_strdup(*result);
			free(*result);
			*result = ft_strjoin(temp, ft_substr(value, *j, i - *j));
		}
		else
			*result = ft_substr(value, *j, i - *j);
	}
}

void	modify_result(char **result, char *replacement)
{
	char	*temp;

	temp = NULL;
	if (*result)
	{
		temp = ft_strdup(*result);
		free(*result);
		*result = ft_strjoin(temp, replacement);
		free(temp);
	}
	else if (replacement)
		*result = ft_strdup(replacement);
}
