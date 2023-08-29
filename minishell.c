/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/08/29 16:23:39 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_tokens(void)
{
	int	i;

	i = -1;
	while (term()->arguments[++i])
	{
		if (ft_strncmp(term()->arguments[i], "ls", 2) == 0)
			execute_ls(term()->arguments[i]);
		else
			printf("[%s] ", term()->arguments[i]);
	}
}

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
		tokenization();
		print_tokens();
		add_history(term()->command);
		clean_mallocs();
		wait(0);
	}
	return (0);
}
