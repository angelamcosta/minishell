/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:12:43 by mpedroso          #+#    #+#             */
/*   Updated: 2023/10/09 17:26:54 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		read_string(void);
void	count_commands(void);
char	*get_var_name(char *value);

char	*get_var_name(char *value)
{
	if (value[0] == '"')
		return (value + 2);
	return (value + 1);
}

int	read_string(void)
{
	int	i;

	i = -1;
	while (term()->command[++i])
	{
		if (term()->command[i] == '|')
		{
			if (i == 0 || (i > 0 && term()->command[i - 1] == '|'))
			{
				printf("parse error near `%c`\n", term()->command[i]);
				term()->exit_status = EXIT_FAILURE;
				return (0);
			}
		}
	}
	return (1);
}

void	count_commands(void)
{
	int			i;
	int			flag;
	t_command	*cmd_list;

	i = 0;
	flag = 1;
	cmd_list = term()->cmd_list;
	while (flag)
	{
		flag = 0;
		if ((cmd_list[i].name != NULL) || (cmd_list[i].args[0] != NULL) || (cmd_list[i].in_red[0] != NULL) || (cmd_list[i].out_red[0] != NULL) || (cmd_list[i].delimiters[0] != NULL) || (cmd_list[i].append[0] != NULL))
			flag = 1;
		if (flag)
			++i;
	}
	term()->count_cmd = i;
}
