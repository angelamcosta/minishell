/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:14:35 by anlima            #+#    #+#             */
/*   Updated: 2023/08/23 14:11:57 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int signum);

void	handle_sigint(int signum)
{
	printf("\n\x1B[35;4mMinishell\x1B[0m ");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
