/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:42 by anlima            #+#    #+#             */
/*   Updated: 2023/09/20 17:10:58 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_env(void);
void	remove_env(char *input);
void	execute_unset(char *str);
void	execute_export(char *str);
void	add_to_env(char *input, char *subs);

void	execute_env(void)
{
	int	i;

	i = -1;
	while (term()->env && term()->env[++i])
		printf("%s%s%s\n", BLUE, term()->env[i], CLEAR);
}

void	remove_env(char *input)
{
	int		i;
	int		j;
	int		flag;
	char	**new_array;

	i = -1;
	flag = 0;
	while (term()->env[++i] != NULL && !flag)
	{
		if (ft_strncmp(term()->env[i], input, ft_strlen(input)) == 0)
			flag = 1;
	}
	if (!flag)
		return ;
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
	int		j;
	char	*subs;
	char	**input;

	input = ft_split(str, ' ');
	i = -1;
	while (input[++i])
	{
		if (ft_strncmp(input[i], "export", 6) == 0)
			continue ;
		else
		{
			j = 0;
			while (input[i][j] != '=')
				j++;
			subs = ft_substr(input[i], 0, j - 1);
			if (subs)
			{
				add_to_env(input[i], subs);
				free(subs);
			}
		}
	}
}

void	add_to_env(char *input, char *subs)
{
	int		i;
	int		j;
	int		flag;
	char	**new_array;

	i = -1;
	flag = 0;
	while (term()->env[++i] != NULL)
	{
		if (ft_strncmp(term()->env[i], subs, ft_strlen(subs)) == 0)
			flag = 1;
	}
	if (flag)
		--i;
	new_array = malloc(sizeof(char *) * (i + 2));
	j = 0;
	i = -1;
	while (term()->env[++i] != NULL)
	{
		if (ft_strncmp(term()->env[i], subs, ft_strlen(subs)) != 0)
		{
			new_array[j] = ft_strdup(term()->env[i]);
			j++;
		}
	}
	new_array[j] = ft_strdup(input);
	new_array[++j] = NULL;
	free_env();
	term()->env = new_array;
}
