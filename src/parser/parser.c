/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:48:47 by anlima            #+#    #+#             */
/*   Updated: 2023/09/23 22:28:10 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(void);
void	add_argument(int j, char *value);
void	handle_variables(int j, char *value);
void	add_red(int j, enum e_TokenType token, char *value);

void	parser(void)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (term()->tokens[++i])
	{
		if (term()->tokens[i]->type == PIPE)
			i++;
		if (term()->tokens[i]->type == CMD)
		{
			j++;
			term()->cmd_list[j].name = ft_strdup(term()->tokens[i]->value);
			term()->cmd_list[j].args[0] = NULL;
		}
		else if (term()->tokens[i]->type == ARG)
			add_argument(j, term()->tokens[i]->value);
		else if (term()->tokens[i]->type == RED_IN
			|| term()->tokens[i]->type == RED_OUT)
			add_red(j, term()->tokens[i]->type, term()->tokens[++i]->value);
		else if (term()->tokens[i]->type == VAR)
			handle_variables(j, term()->tokens[i]->value);
		printf("Processed Token %d: %s\tj: %i\n", i, term()->tokens[i]->value, j);
	}
}

void	add_argument(int j, char *value)
{
	int	i;

	i = 0;
	while (term()->cmd_list[j].args[i] != NULL)
		i++;
	term()->cmd_list[j].args[i] = ft_strdup(value);
}

void	add_red(int j, enum e_TokenType token, char *value)
{
	if (token == RED_IN)
		term()->cmd_list[j].in_red = ft_strdup(value);
	else
		term()->cmd_list[j].out_red = ft_strdup(value);
}

void	handle_variables(int j, char *value)
{
	int		i;
	int		flag;
	char	*var_name;

	i = -1;
	flag = 0;
	var_name = value + 1;
	while (term()->env[++i] != NULL && !flag)
	{
		if (ft_strncmp(term()->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			flag = 1;
			break ;
		}
	}
	if (flag)
		add_argument(j, term()->env[i] + ft_strlen(var_name) + 1);
}
