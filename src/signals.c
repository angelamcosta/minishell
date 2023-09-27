/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:14:35 by anlima            #+#    #+#             */
/*   Updated: 2023/09/27 22:43:35 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_signals(void);
void	handle_sig_c(int sig);

void	set_signals(void)
{
	signal(SIGINT, handle_sig_c);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sig_c(int sig)
{
	if (sig == SIGINT)
	{
		if (term()->in_cmd)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			return ;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
