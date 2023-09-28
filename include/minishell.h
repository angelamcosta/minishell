/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:48:28 by anlima            #+#    #+#             */
/*   Updated: 2023/09/28 15:50:18 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define CLEAR "\033[0m"
# define RED "\033[91;1m"
# define BLUE "\033[94;1m"
# define PINK "\033[95;1m"
# define GREEN "\033[92;1m"
# define YELLOW "\033[93;1m"
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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
# define LEN 25
# define PROMPT "\001\e[38;5;206m\002Minishell\001\e[0m\002 ➜ "
# define NOT_FOUND 127

enum					e_TokenType
{
	CMD = 1,
	ARG,
	VAR,
	PIPE,
	APPEND,
	RED_IN,
	RED_OUT,
	HEREDOC
};

typedef struct s_token
{
	enum e_TokenType	type;
	char				*value;
}						t_token;

typedef struct s_command
{
	char				*name;
	char				*args[MAX_TOKENS];
	char				*in_red[LEN];
	char				*out_red[LEN];
	char				*delimiters[LEN];
}						t_command;

typedef struct s_term
{
	char				*user;
	char				*home;
	char				**env;
	char				*command;
	t_token				**tokens;
	t_command			cmd_list[MAX_TOKENS];
	int					exit_status;
	int					pipe_fd[2];
	int					in_cmd;
}						t_term;

// buitins
void					execute_exit(void);
void					execute_clear(void);
void					execute_echo(char **args);
void					execute_cd(char **args);
void					execute_pwd(char **args);
void					execute_env(char **arg);
void					remove_env(char *input);
void					execute_unset(char **input);
void					execute_export(char **input);
void					add_to_env(char *input, char *subs);
// executor
void					executor(void);
void					execute_red(t_command *cmd);
void					execute_command(t_command *cmd, char *path);
void					execute_in(t_command *cmd, char *filename, char *path);
void					execute_out(t_command *cmd, char *filename, char *path);
void					create_pipe(void);
char					*get_path(char *cmd_name);
void					find_command(t_command *cmd);
void					set_pipes(t_command *cmd, int fd_in, int fd_out);
// parser
void					lexer(void);
void					grammar(void);
int						grammar_check(int i);
int						check_quotes(char *str);
void					tokenize_input(char *str);
void					add_token(char *input, int i, int flag);
void					parser(void);
void					add_red(char **cmd_list, char *value);
void					add_argument(t_command *cmd, char *value);
void					handle_variables(t_command *cmd, char *value);
void					add_command(t_command *cmd, t_token **tokens);
// free memory
void					free_tokens(void);
void					clean_mallocs(void);
void					free_commands(void);
// general
void					error_status(char *function, int err);
t_term					*term(void);
void					free_env(void);
int						is_env(char *subs);
void					set_env(char **input);
void					init_program(char **env);
// signals
void					set_signals(void);
void					handle_sig_c(int sig);

#endif