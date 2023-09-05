/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/09/02 11:31:14 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// void	execute_cmds(void)
// {
// 	int	i;

// 	i = -1;
// 	while (term()->cmd_table[++i])
// 	{
// 		// if (ft_strncmp(term()->cmd_table[i], "ls", 2) == 0)
// 		// 	execute_ls(term()->cmd_table[i]);
// 		// else
// 			printf("[%s] ", term()->cmd_table[i]);
// 	}
// 	printf("\n");
// }

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
			free(term()->command);
			continue ;
		}
		lexer();
		parser();
		add_history(term()->command);
		clean_mallocs();
		wait(0);
	}
	return (0);
}
