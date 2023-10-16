/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:09:57 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 19:49:44 by anlima           ###   ########.fr       */
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
	int		j;
	int		k;
	int		quote;
	char	**strs;
	char	*subs;
	char	*temp;

	i = -1;
	k = -1;
	j = 0;
	quote = 0;
	strs = (char **)malloc(sizeof(char *) * (count_words(input) + 1));
	while (++i < (int)ft_strlen(input) && count_words(input))
	{
		while (input[i] == ' ' && quote == 0)
		{
			i++;
			if (input[i] != ' ')
				j = i;
		}
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		if ((input[i + 1] == '\0' || input[i + 1] == ' ') && quote == 0)
		{
			subs = ft_substr(input, j, i + 1 - j);
			if (should_expand(subs))
			{
				temp = expand_var(subs);
				if (temp != NULL)
					strs[++k] = ft_strdup(temp);
			}
			else
				strs[++k] = ft_strdup(subs);
		}
		if ((input[i - 1] == ' ' && quote == 0) || (input[i] == quote && input[i
				- 1] == ' ' && input[i] != '\0'))
			j = i;
	}
	strs[++k] = NULL;
	return (strs);
}

char	*expand_var(char *value)
{
	int		i;
	int		j;
	int		quote;
	char	*var_name;
	char	*replacement;
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
		{
			if (quote == 0)
				quote = value[i];
			else if (quote == value[i])
				quote = 0;
		}
		else if (value[i] == '$')
		{
			if (i - j > 0)
			{
				if (result)
					result = ft_strjoin(result, ft_substr(value, j, i - j));
				else
					result = ft_substr(value, j, i - j);
			}
			j = i;
			var_name = extract_varname(&value[i]);
			replacement = handle_variables(var_name);
			while (value[++j])
			{
				if (value[j] == ' ' || !ft_isalnum(value[j]))
					break ;
			}
			if (result)
				result = ft_strjoin(result, replacement);
			else
				result = replacement;
		}
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
	if (ft_strncmp(value, "?", 2) == 0)
		return (ft_itoa(term()->exit_status));
	while (term()->env[++i] != NULL && !flag)
	{
		if (ft_strncmp(term()->env[i], value, ft_strlen(value)) == 0)
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
