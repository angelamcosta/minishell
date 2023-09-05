/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:36:42 by anlima            #+#    #+#             */
/*   Updated: 2023/09/02 11:53:28 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_command(char *token)
{
	if (ft_strncmp("ls", token, 2) == 0 || ft_strncmp("echo", token, 4) == 0
		|| ft_strncmp("pwd", token, 3) == 0)
		return (1);
	return (0);
}
