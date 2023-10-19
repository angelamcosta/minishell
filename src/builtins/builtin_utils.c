/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:52:47 by anlima            #+#    #+#             */
/*   Updated: 2023/10/19 21:39:31 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		can_fork(t_command *cmd);
int		treat_exit_arg(char *str);
void	print_sorted_env(int flag);
int		is_valid_varname(char *str);
void	insertion_sort(char **arr, int n);

int	is_valid_varname(char *str)
{
	int	i;

	i = -1;
	if (!str || *str == '\0')
		return (0);
	while (str[++i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
	}
	return (1);
}

int	can_fork(t_command *cmd)
{
	if (!cmd->name && cmd->args[0] && ft_isdigit(*cmd->args[0]))
	{
		print_str(cmd->args[0]);
		write(1, "\n", 1);
		return (0);
	}
	else if (cmd->name && ((ft_strncmp(cmd->name, "exit", 5) == 0)
			|| (ft_strncmp(cmd->name, "cd", 3) == 0) || (ft_strncmp(cmd->name,
					"env", 4) == 0) || (ft_strncmp(cmd->name, "unset", 6) == 0)
			|| (ft_strncmp(cmd->name, "export", 7) == 0)))
		return (0);
	return (1);
}

int	treat_exit_arg(char *str)
{
	int	i;
	int	nb;
	int	flag;

	i = 0;
	nb = 0;
	flag = 0;
	while (str[i] == '"' || str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag = 1;
		i++;
	}
	nb = ft_atoi(&str[i]);
	if (flag)
		nb *= -1;
	return (nb);
}

void	insertion_sort(char **arr, int n)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (++i < n)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && strcmp(arr[j], key) > 0)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void	print_sorted_env(int flag)
{
	int		i;
	int		env_count;
	char	**env_copy;

	i = -1;
	env_count = 0;
	while (term()->env && term()->env[env_count] != NULL)
		env_count++;
	env_copy = (char **)malloc(sizeof(char *) * (env_count + 1));
	while (++i < env_count)
		env_copy[i] = term()->env[i];
	env_copy[env_count] = NULL;
	insertion_sort(env_copy, env_count);
	i = -1;
	while (++i < env_count)
	{
		if (flag)
			printf("export -x %s\n", env_copy[i]);
		else if (ft_strchr(env_copy[i], '='))
		{
			print_str(env_copy[i]);
			printf("\n");
		}
	}
	free(env_copy);
}
