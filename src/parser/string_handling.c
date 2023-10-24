/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:09:57 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 15:42:07 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_var(char *value);
char	*get_var_name(char *value);
char	*extract_varname(char *str);
char	**split_command(char *input);
char	*handle_variables(char *value);

char	**split_command(char *input)
{
	int		i;
	int		k;
	int		start;
	int		quote;
	char	**strs;

	i = 0;
	k = -1;
	quote = 0;
	strs = (char **)malloc(sizeof(char *) * (count_words(input) + 1));
	while (input[i])
	{
		while (input[i] == ' ' && quote == 0)
			i++;
		start = i;
		while (input[i] && ((input[i] != ' ' && quote == 0) || quote))
		{
			if (input[i] == '"' || input[i] == '\'')
				change_quote(&quote, input[i]);
			i++;
		}
		should_add(&input[start], i - start, strs, &k);
	}
	strs[++k] = NULL;
	return (strs);
}

char	*expand_var(char *value)
{
	int		i;
	int		j;
	int		quote;
	char	*result;

	i = -1;
	j = 0;
	quote = 0;
	result = NULL;
	while (++i <= (int)ft_strlen(value))
	{
		while (value[i] == ' ' && quote == 0)
		{
			i++;
			if (value[i] != ' ')
				j = i;
		}
		if (value[i] == '"' || value[i] == '\'')
			change_quote(&quote, value[i]);
		else if (value[i] == '$')
			treat_expasion(i, &j, &result, value);
		else if (value[i] == '\0' && j != i)
			result = ft_strjoin(result, ft_substr(value, j, i - j));
	}
	return (result);
}

char	*get_var_name(char *value)
{
	if (value[0] == '"')
		return (value + 2);
	return (value + 1);
}

char	*extract_varname(char *str)
{
	int	i;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 1, i - 1));
}

char	*handle_variables(char *value)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (term()->env[++i] != NULL && !flag)
	{
		if (ft_strncmp(term()->env[i], value, ft_strlen(value)) == 0
			&& (*(term()->env[i] + ft_strlen(value)) == '='))
		{
			flag = 1;
			break ;
		}
	}
	if (flag)
		return (ft_strdup(term()->env[i] + ft_strlen(value) + 1));
	else
		return (NULL);
}
