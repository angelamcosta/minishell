/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:55:11 by anlima            #+#    #+#             */
/*   Updated: 2023/06/08 00:05:59 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_term	*term(void);
void	clean_mallocs(void);

t_term	*term(void)
{
	static t_term	term;

	return (&term);
}

void	clean_mallocs(void)
{
	if (term()->str)
		free(term()->str);
}
