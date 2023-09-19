/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/09/19 23:20:40 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	signal(SIGINT, handle_sig_c);
	signal(SIGQUIT, SIG_IGN);
	set_env(env);
	term()->user = getenv("USER");
	term()->home = getenv("HOME");
	while (1)
	{
		rl_on_new_line();
		term()->command = readline("\x1B[35;4mMinishell\x1B[0m ➜ ");
		if (term()->command == NULL)
			break ;
		if (*term()->command == '\0')
		{
			clean_mallocs();
			continue ;
		}
		trim_argument(&term()->command);
		lexer();
		add_history(term()->command);
		clean_mallocs();
	}
	clean_mallocs();
	return (0);
}
