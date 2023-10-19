/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:48:28 by anlima            #+#    #+#             */
/*   Updated: 2023/10/19 22:29:11 by anlima           ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define MAX_TOKENS 100
# define HERETXT "temp_here.txt"
# define LEN 25
# define PROMPT "\001\e[38;5;206m\002Minishell\001\e[0m\002 ➜ "
# define NOT_FOUND 127
# define IS_DIRECTORY 126
# define ERR_PERMISSION 126
# define BUFF_SIZE 1024

extern int				g_exit;

enum					e_TokenType
{
	CMD = 1,
	ARG,
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
	char				*append[LEN];
	char				*in_red[LEN];
	char				*out_red[LEN];
	char				*delimiters[LEN];
	char				*args[MAX_TOKENS];
}						t_command;

typedef struct s_term
{
	int					count_cmd;
	int					pipe_fd[2];
	char				*user;
	char				*home;
	char				*command;
	char				**env;
	t_token				**tokens;
	t_command			cmd_list[MAX_TOKENS];
}						t_term;

// buitins
int						can_fork(t_command *cmd);
int						treat_exit_arg(char *str);
void					print_sorted_env(int flag);
int						is_valid_varname(char *str);
void					insertion_sort(char **arr, int n);
void					handle_heredocs(void);
void					heredoc(char *delimiter);
void					execute_clear(void);
void					print_str(char *str);
int						is_numeric(char *arg);
void					execute_echo(char **args);
void					execute_exit(char **args);
void					execute_pwd(void);
void					execute_cd(char **args);
void					remove_env(char *input);
void					execute_unset(char **input);
void					execute_export(char **input);
void					execute_env(char **arg, int flag);
void					add_to_env(char *input, char *subs);
// executor
char					**check_path(void);
char					*get_path(char *cmd_name);
void					execute_command(t_command *cmd, char *path);
void					fork_builtin(void);
int						check_flag(char *input);
int						is_builtin(char *cmd_name);
void					execute_builtin(t_command *cmd);
void					executor(void);
void					execute_in(char *filename);
void					execute_red(t_command *cmd);
void					execute_out(char *filename, int flag);
void					create_pipe(void);
void					set_pipes(int fd_in, int fd_out);
pid_t					create_fork(t_command *cmd, int fd_in, int fd_out);
// parser
// command parsing
void					count_commands(void);
char					**ft_split_pipes(char *input);
void					add_red(char **cmd_list, char *value);
void					add_argument(t_command *cmd, char *value);
void					add_command(t_command *cmd, t_token **tokens);
// parser
void					lexer(void);
void					parser(void);
// parsing_utils
int						count_pipes(char *input);
char					*dup_quoted(char *value);
// string_handling
char					*expand_var(char *value);
char					*get_var_name(char *value);
char					*extract_varname(char *str);
char					**split_command(char *input);
char					*handle_variables(char *value);
// syntax_parsing
void					grammar(void);
int						read_string(void);
int						check_quotes(char *str);
int						should_expand(char *input);
void					change_quote(int *quote, char input);
// tokenization
void					tokenize_input(void);
int						count_words(char *input);
void					add_token(char *input, int *i, int flag);
void					set_token_type(t_token *token, char *input, int flag);
void					add_tokens_from_command(char *command,
							int *token_index);
// free memory
void					clean_mallocs(void);
void					free_token(t_token *token);
void					free_command(t_command *cmd);
void					free_term(t_term *term);
// general
t_term					*term(void);
void					free_env(void);
int						is_env(char *subs);
void					set_env(char **input);
void					init_program(char **env);
// signals
void					set_signals(void);
void					signals_child(void);
void					handle_sig_c(int sig);
void					handle_fork_signals(int sig);

#endif