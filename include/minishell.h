/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:48:28 by anlima            #+#    #+#             */
/*   Updated: 2023/08/18 16:44:05 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RED "\033[91;1m"
# define GREEN "\033[92;1m"
# define YELLOW "\033[93;1m"
# define BLUE "\033[94;1m"
# define PINK "\033[95;1m"
# define CLEAR "\033[0m"
# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

extern char	**environ;

typedef struct s_term
{
	char	*user;
	char	*home;
	char	*command;
	char	**arguments;
	char	**env;
	char	**tokens;
}	t_term;

t_term	*term(void);
void	parse_input(void);
void	execute_ls(void);
// void	execute_exit(void);
void	tokenize_input(void);
void	execute_echo(void);
void	execute_clear(void);
void	execute_cd(void);
void	execute_pwd(void);
void	execute_env(void);
// void	execute_unset(void);
void	execute_export(void);

#endif