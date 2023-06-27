/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:47:34 by anlima            #+#    #+#             */
/*   Updated: 2023/06/27 23:47:26 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(void)
{
	term()->user = getenv("USER");
	term()->home = getenv("HOME");
	while (1)
	{
		printf("%s ", term()->user);
		term()->command = readline(">> ");
		tokenize_input();
		if (term()->arguments[0] != NULL)
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
		}
		free(term()->command);
		free(term()->arguments);
	}

	return (0);
}
