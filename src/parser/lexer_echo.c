/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:09:57 by anlima            #+#    #+#             */
/*   Updated: 2023/10/13 17:28:46 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		count_words(char *input);
char	**treat_echo(char *input);
char	*expand_var(char *value);
char	*extract_varname(char *str);
int		should_expand(char *input);

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
	while (i <= ft_strlen(input))
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
			if (i >= ft_strlen(input))
				break ;
		}
		else
			i++;
	}
	strs[++k] = NULL;
	return (strs);
}

int	count_words(char *input)
{
	int	i;
	int	j;
	int	quote;

	i = 4;
	j = 0;
	quote = 0;
	while (input[++i])
	{
		if (input[i] == ' ' && quote == 0)
		{
			while (input[i] == ' ' && quote == 0)
				i++;
			if (input[i] != '\0')
				j++;
			else
				break ;
		}
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
	}
	return (j);
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

char	*extract_varname(char *str)
{
	int	i;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 1, i - 1));
}

int	should_expand(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 1;
	while (input[i])
	{
		if (input[i] == '"' && ft_strrchr(input, '$'))
			return (1);
		if (input[i] == '\'')
			return (0);
		i++;
	}
	if (ft_strrchr(input, '$'))
		return (1);
	return (0);
}
