/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:36:42 by anlima            #+#    #+#             */
/*   Updated: 2023/09/13 13:40:57 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	opened_quote(char *str);
void	handle_quotes(char **arg);
int		is_valid_argument(char *arg);
int		is_valid_red(char **tokens, int i);

char	opened_quote(char *str)
{
	int		i;
	char	opened_quote;

	i = -1;
	opened_quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (opened_quote == 0)
				opened_quote = str[i];
			else if (opened_quote == str[i])
				opened_quote = 0;
		}
	}
	return (opened_quote);
}

void	handle_quotes(char **arg)
{
	char	*input;
	char	*temp;
	char	quote;

	while (!is_valid_argument(*arg))
	{
		quote = opened_quote(*arg);
		if (quote == '\'')
			input = readline("quote> ");
		else
			input = readline("dquote> ");
		temp = ft_strdup(*arg);
		free(*arg);
		*arg = ft_strjoin(temp, ft_strjoin("\n", input));
		free(temp);
		temp = ft_strdup(term()->command);
		free(term()->command);
		(term()->command) = ft_strjoin(temp, (ft_strjoin("\n", input)));
		free(temp);
		free(input);
	}
}

int	is_valid_argument(char *arg)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = -1;
	single_quotes = 0;
	double_quotes = 0;
	while (arg[++i])
	{
		if (arg[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		else if (arg[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
	}
	if (double_quotes || single_quotes)
		return (0);
	return (1);
}

int	is_valid_red(char **tokens, int i)
{
	int			j;
	static char	*valid_red[] = {"|", "||", "&&", "&", NULL};

	j = -1;
	while (valid_red[++j])
	{
		if (ft_strncmp(tokens[i], valid_red[j], ft_strlen(valid_red[j])) == 0
			|| ft_strncmp(tokens[i], valid_red[j], ft_strlen(valid_red[j])) == 0
			|| ft_strncmp(tokens[i], valid_red[j],
				ft_strlen(valid_red[j])) == 0)
		{
			if (tokens[i + 1] == NULL)
			{
				printf("Error: Invalid redirection\n");
				return (0);
			}
		}
	}
	return (1);
}
