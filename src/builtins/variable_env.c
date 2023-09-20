/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:42 by anlima            #+#    #+#             */
/*   Updated: 2023/09/20 22:22:48 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_env(char *arg);
void	remove_env(char *input);
void	execute_unset(char *str);
void	execute_export(char *str);
void	add_to_env(char *input, char *subs);

void	execute_env(char *arg)
{
	int		i;
	char	**input;

	i = -1;
	if (ft_strncmp(arg, "env", 3) == 0)
	{
		if (arg[3] != '\0')
		{
			printf("env: too many arguments\n");
			return ;
		}
	}
	i = -1;
	while (term()->env && term()->env[++i])
	{
		if (ft_strchr(term()->env[i], '='))
			printf("%s%s%s\n", BLUE, term()->env[i], CLEAR);
	}
}

void	remove_env(char *input)
{
	int		i;
	int		j;
	int		flag;
	char	**new_array;

	i = 0;
	flag = is_env(input);
	if (!flag)
		return ;
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
			if (input[i])
				remove_env(input[i]);
		}
	}
}

void	execute_export(char *str)
{
	int		i;
	char	*subs;
	char	**input;

	input = ft_split(str, ' ');
	i = -1;
	while (input[++i])
	{
		if (ft_strncmp(input[i], "export", 6) == 0)
			continue ;
		subs = ft_strchr(input[i], '=');
		if (!subs)
			add_to_env(input[i], input[i]);
		else
		{
			subs = ft_substr(input[i], 0, subs - input[i]);
			if (subs)
			{
				add_to_env(input[i], subs);
				free(subs);
			}
		}
	}
	// if (i == 1)
	// 	execute_env("declare -x ");
}

void	add_to_env(char *input, char *subs)
{
	int		i;
	int		j;
	int		flag;
	char	**new_array;

	i = 0;
	flag = is_env(subs);
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
