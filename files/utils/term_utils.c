/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:03:20 by anlima            #+#    #+#             */
/*   Updated: 2023/06/08 00:24:14 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_command(char *str);

void	process_command(char *str)
{
	if (ft_strncmp(str, "exit", 3))
	{
		clean_mallocs();
		printf("exit\n");
		exit(0);
	}
	else if (ft_strncmp(str, "echo", 3))
		printf("%s\n", &str[5]);
}
