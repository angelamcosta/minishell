/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:42 by anlima            #+#    #+#             */
/*   Updated: 2023/10/17 17:55:26 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_env(char **arg);
void	remove_env(char *input);
void	execute_unset(char **input);
void	execute_export(char **input);
void	add_to_env(char *input, char *subs);

void	execute_env(char **arg)
{
	int	i;

	if (arg[1] != NULL)
	{
		g_exit = EXIT_FAILURE;
		printf("%s\n", "env: too many arguments");
	}
	else
	{
		i = -1;
		while (term()->env && term()->env[++i])
		{
			if (ft_strchr(term()->env[i], '='))
				printf("%s\n", term()->env[i]);
		}
		g_exit = EXIT_SUCCESS;
	}
}

void	remove_env(char *input)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	while (term()->env[++i] != NULL)
		i++;
	new_array = (char **)malloc(sizeof(char *) * (i));
	j = 0;
	i = -1;
	while (term()->env[++i] != NULL)
	{
		if (ft_strncmp(term()->env[i], input, ft_strlen(input)) != 0)
		{
			new_array[j] = ft_strdup(term()->env[i]);
			j++;
		}
	}
	new_array[j] = NULL;
	free_env();
	term()->env = new_array;
	g_exit = EXIT_SUCCESS;
}

void	execute_unset(char **input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (ft_strncmp(input[i], "unset", 5) == 0)
			continue ;
		else
		{
			if (input[i] && is_env(input[i]))
				remove_env(input[i]);
		}
	}
	g_exit = EXIT_SUCCESS;
}

void	execute_export(char **input)
{
	int		i;
	char	*subs;

	i = -1;
	while (input[++i])
	{
		if (ft_strncmp(input[i], "export", 6) == 0)
			continue ;
		subs = ft_strchr(input[i], '=');
		if (!subs && is_valid_varname(input[i]))
			add_to_env(input[i], input[i]);
		else
		{
			subs = ft_substr(input[i], 0, subs - input[i]);
			if (subs && is_valid_varname(subs))
			{
				add_to_env(input[i], subs);
				g_exit = EXIT_SUCCESS;
			}
			else
				g_exit = EXIT_FAILURE;
			free(subs);
		}
	}
}

void	add_to_env(char *input, char *subs)
{
	int		i;
	int		j;
	int		flag;
	char	**new_array;

	i = 0;
	flag = is_env(subs);
	if (!is_valid_varname(subs))
		return ;
	while (term()->env[++i] != NULL)
		i++;
	if (flag)
		--i;
	new_array = malloc(sizeof(char *) * (i + 2));
	j = 0;
	i = -1;
	while (term()->env[++i] != NULL)
	{
		if (ft_strncmp(term()->env[i], subs, ft_strlen(subs)) != 0)
			new_array[j++] = ft_strdup(term()->env[i]);
	}
	new_array[j] = ft_strdup(input);
	new_array[++j] = NULL;
	free_env();
	term()->env = new_array;
}
