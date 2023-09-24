/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:14:35 by anlima            #+#    #+#             */
/*   Updated: 2023/09/24 19:59:52 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_signals(void);
void	handle_sig_c(int sig);
void	handle_sigint(int signum);

void	set_signals(void)
{
	signal(SIGINT, handle_sig_c);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int signum)
{
	printf(PROMPT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
