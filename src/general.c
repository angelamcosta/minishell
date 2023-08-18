/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:49:20 by anlima            #+#    #+#             */
/*   Updated: 2023/08/18 17:13:49 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_term	*term(void);

t_term	*term(void)
{
	static t_term	term;

	return (&term);
}

void	parse_input(void)
{
	if (ft_strncmp(term()->arguments[0], "cd",
			ft_strlen(term()->arguments[0])) == 0)
		execute_cd();
	else if (ft_strncmp(term()->arguments[0], "pwd",
			ft_strlen(term()->arguments[0])) == 0)
		execute_pwd();
	else if (ft_strncmp(term()->arguments[0], "export",
			ft_strlen(term()->arguments[0])) == 0)
		execute_export();
	else if (ft_strncmp(term()->arguments[0], "env",
			ft_strlen(term()->arguments[0])) == 0)
		execute_env();
	else if (ft_strncmp(term()->arguments[0], "ls",
			ft_strlen("ls")) == 0)
		execute_ls();
	else if (ft_strncmp(term()->arguments[0], "echo",
			ft_strlen("echo")) == 0)
		execute_echo();
	else if (ft_strncmp(term()->arguments[0], "clear",
			ft_strlen("clear")) == 0)
		execute_clear();
	else
		printf("%scommand not found: %s%s\n", BLUE, term()->arguments[0], CLEAR);
}
