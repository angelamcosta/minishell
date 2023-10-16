/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:09:57 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 15:56:08 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_var(char *value);
char	**treat_echo(char *input);
char	*get_var_name(char *value);
char	*extract_varname(char *str);
char	*handle_variables(char *value);

char	**treat_echo(char *input)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	**strs;

	i = 4;
	k = -1;
	quote = 0;
	strs = (char **)malloc(sizeof(char *) * (count_words(input) + 2));
	strs[++k] = ft_strdup("echo");
	while (input[i] == ' ')
		i++;
	j = i;
	while (i <= (int)(ft_strlen(input)))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i - 1] == ' ' && quote == 0)
			j = i;
		if ((input[i] == '\0' || input[i] == ' ') && quote == 0)
		{
			strs[++k] = ft_substr(input, j, i - j);
			while (input[i] != '\0' && input[i] == ' ' && quote == 0)
				i++;
			if (i >= (int)(ft_strlen(input)))
				break ;
		}
		else
			i++;
	}
	strs[++k] = NULL;
	return (strs);
}

char	*expand_var(char *value)
{
	int		i;
	int		j;
	char	*var_name;
	char	*replacement;
	char	*result;

	i = 0;
	j = 0;
	result = NULL;
	while (value[i])
	{
		if (value[i] == '$')
		{
			if (i - 1 > 0)
			{
				if (result)
					result = ft_strjoin(result, ft_substr(value, j, i - j));
				else
					result = ft_substr(value, j, i - j);
			}
			var_name = extract_varname(&value[i]);
			replacement = handle_variables(var_name);
			if (replacement)
			{
				if (result)
					result = ft_strjoin(result, replacement);
				else
					result = replacement;
				i += (ft_strlen(var_name) + 1);
				j = i;
			}
		}
		if (value[i] != '\0')
			i++;
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
