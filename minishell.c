/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/09/21 15:44:46 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	init_program(env);
	while (1)
	{
		rl_on_new_line();
		term()->command = readline(PROMPT);
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
