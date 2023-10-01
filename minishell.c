/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/10/01 15:13:32 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_command(const t_command *cmd);

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
			continue ;
		lexer();
		add_history(term()->command);
		clean_mallocs();
	}
	return (0);
}

// TODO: - HEREDOC
// TODO: - make the exist status work
// TODO: - throw error when command doesnt exist
