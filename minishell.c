/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/10/24 19:19:04 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_exit = 0;

int	main(int argc, char **argv, char **env)
{
	(void)(argc);
	(void)(argv);
	init_program(env);
	while (1)
	{
		rl_on_new_line();
		term()->command = readline(PROMPT);
		if (term()->command == NULL)
			break ;
		if (*term()->command == '\0')
			continue ;
		lexer();
		add_history(term()->command);
		clean_mallocs();
		remove(HERETXT);
	}
	free_env();
	return (0);
}

// TODO: - ctrl c in child process prints minishell twice, fix it
