/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:48:28 by anlima            #+#    #+#             */
/*   Updated: 2023/09/20 17:09:42 by anlima           ###   ########.fr       */
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
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define MAX_TOKENS 100
# define MAX_TOKEN_LENGTH 100

typedef struct s_term
{
	char	*user;
	char	*home;
	char	**env;
	char	*command;
	char	**cmd_table;
}			t_term;

// buitins
void		execute_exit(void);
void		execute_clear(void);
void		execute_echo(char *token);
void		execute_cd(char *str);
void		execute_pwd(char *str);
void		execute_env(void);
void		remove_env(char *input);
void		execute_unset(char *str);
void		execute_export(char *str);
void		add_to_env(char *input, char *subs);
// executor
void		executor(void);
// parser
void		trim_argument(char **arg);
void		handle_token(int *i, int *j);
void		handle_error(char **input, int i);
int			is_inside_quotes(char *input, int i);
void		add_cmd(char *input, int start, int i, int *j);
void		lexer(void);
void		handle_red(void);
void		handle_quotes(void);
char		opened_quote(char *str);
int			is_valid_argument(char *arg);
int			is_valid_red(char **tokens, int i);
void		parser(void);
// utils
void		handle_sig_c(int sig);
// free memory
void		clean_mallocs(void);
// general
t_term		*term(void);
void		free_env(void);
void		set_env(char **input);
// signals
void		handle_sigint(int signum);

#endif