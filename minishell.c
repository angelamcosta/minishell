/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/09/13 16:17:11 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	int	i;

	signal(SIGINT, handle_sigint);
	term()->env = env;
	term()->user = getenv("USER");
	term()->home = getenv("HOME");
	while (1)
	{
		i = 0;
		printf("\x1B[35;4mMinishell\x1B[0m ");
		term()->command = readline("➜ ");
		if (term()->command == NULL)
			break ;
		if (*term()->command == '\0')
		{
			clean_mallocs();
			continue ;
		}
		lexer();
		add_history(term()->command);
		clean_mallocs();
	}
	clean_mallocs();
	return (0);
}
