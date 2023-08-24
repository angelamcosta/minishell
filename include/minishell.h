/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:48:28 by anlima            #+#    #+#             */
/*   Updated: 2023/08/24 14:42:42 by anlima           ###   ########.fr       */
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
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define MAX_TOKENS 100
# define MAX_TOKEN_LENGTH 100

extern char	**environ;

typedef struct s_term
{
	char	*user;
	char	*home;
	char	*command;
	char	**arguments;
	char	**env;
	char	**tokens;
}			t_term;

// buitins
void	execute_ls(void);
void	execute_exit(void);
void	execute_echo(void);
void	execute_clear(void);
void	execute_cd(void);
void	execute_pwd(void);
void	execute_env(void);
void	execute_unset(void);
void	execute_export(void);
// tokens
int		is_token(char *input, int i);
int		trim_whitespaces(char *input, int i);
void 	add_token(char *input, char **args, int i, int j);
void	toggle_state(char *input, int i, int *single_quotes,
			int *double_quotes);
// general
t_term	*term(void);
void	parse_input(void);
// lexer
int		is_delimiter(char c);
// parsing
void	tokenize_input(void);
// signals
void	handle_sigint(int signum);

#endif