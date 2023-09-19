/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:42 by anlima            #+#    #+#             */
/*   Updated: 2023/09/20 00:23:24 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_env(void);
void	add_to_env(char *input);
void	remove_env(char *input);
void	execute_unset(char *str);
void	execute_export(char *str);

void	execute_env(void)
{
	int	i;

	i = -1;
	while (term()->env && term()->env[++i])
		printf("%s%s%s\n", BLUE, term()->env[i], CLEAR);
}

void	add_to_env(char *input)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	while (term()->env[i] != NULL)
		i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	j = -1;
	while (++j < i)
		new_array[j] = ft_strdup(term()->env[j]);
	new_array[j] = ft_strdup(input);
	new_array[++j] = NULL;
	i = -1;
	while (term()->env[++i] != NULL)
	{
		if (term()->env[i])
			free(term()->env[i]);
	}
	free(term()->env);
	term()->env = new_array;
}


void	remove_env(char *input)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	while (term()->env[i] != NULL)
		i++;
	new_array = malloc(sizeof(char *) * (i));
	j = -1;
	while (++j < i)
	{
		if (ft_strncmp(input, term()->env[j], ft_strlen(input)) == 0)
			continue ;
		new_array[j] = ft_strdup(term()->env[j]);
	}
	new_array[++j] = NULL;
	i = -1;
	while (term()->env[++i] != NULL)
	{
		if (term()->env[i])
			free(term()->env[i]);
	}
	free(term()->env);
	term()->env = new_array;
}

void	execute_unset(char *str)
{
	int		i;
	int		j;
	char	*subs;
	char	**input;

	input = ft_split(str, ' ');
	i = -1;
	while (input[++i])
	{
		if (ft_strncmp(input[i], "unset", 5) == 0)
			continue ;
		else
		{
			j = 0;
			while (input[i][j] != '=')
				j++;
			subs = ft_substr(input[i], 0, j - 1);
			if (subs)
			{
				remove_env(subs);
				free(subs);
			}
		}
	}
}

void	execute_export(char *str)
{
	int		i;
	char	**input;

	input = ft_split(str, ' ');
	i = -1;
	while (input[++i])
	{
		if (ft_strncmp(input[i], "export", 6) == 0)
			continue ;
		else
			add_to_env(input[i]);
	}
}
