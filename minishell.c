/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/08/18 16:34:59 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	term()->user = getenv("USER");
	term()->home = getenv("HOME");
	term()->env = env;
	while (1)
	{
		printf("\x1B[35;4mMinishell\x1B[0m ");
		term()->command = readline("➜  ");
		tokenize_input();
		if (term()->arguments[0] != NULL)
			parse_input();
		add_history(term()->command);
		free(term()->command);
		free(term()->arguments);
	}
	return (0);
}
