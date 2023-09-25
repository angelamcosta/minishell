/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:45:31 by anlima            #+#    #+#             */
/*   Updated: 2023/09/25 21:25:25 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer(void);
void	grammar(void);
int		check_quotes(char *str);
void	tokenize_input(char *str);
void	add_token(char *input, int i, int flag);

void	lexer(void)
{
	if (!check_quotes(term()->command))
	{
		printf("parse error; unbalanced quotes\n");
		term()->exit_status = EXIT_FAILURE;
		return ;
	}
	tokenize_input(term()->command);
	grammar();
}

void	add_token(char *input, int i, int flag)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (flag)
		token->type = CMD;
	else if (ft_strncmp(input, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(input, "<<", 2) == 0)
		token->type = HEREDOC;
	else if (input[0] == '|' || input[0] == '&')
		token->type = PIPE;
	else if (input[0] == '<')
		token->type = RED_IN;
	else if (input[0] == '>')
		token->type = RED_OUT;
	else if (input[0] == '$' || (input[0] == '"' && input[1] == '$'))
		token->type = VAR;
	else
		token->type = ARG;
	token->value = ft_strdup(input);
	term()->tokens[i] = token;
}

void	grammar(void)
{
	int		i;
	t_token	**tokens;

	i = -1;
	tokens = term()->tokens;
	while (tokens && tokens[++i])
	{
		if (tokens[i + 1] && (tokens[i]->type == tokens[i + 1]->type)
			&& (tokens[i]->type != ARG && tokens[i]->type != VAR) 
			|| (!tokens[i + 1] && (tokens[i]->type == RED_IN 
					|| tokens[i]->type == RED_OUT) || tokens[i]->type == APPEND 
				|| tokens[i]->type == HEREDOC))
		{
			printf("parse error near `%s`\n", tokens[i]->value);
			term()->exit_status = EXIT_FAILURE;
			return ;
		}
	}
	parser();
}

int	check_quotes(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str && str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i];
		else if ((str[i] == '"' || str[i] == '\'') && quote == str[i])
			quote = 0;
	}
	if (quote != 0)
		return (0);
	return (1);
}

void	tokenize_input(char *str)
{
	int		i;
	char	**input;

	i = 0;
	input = ft_split(term()->command, ' ');
	term()->tokens = (t_token **)malloc(sizeof(t_token *) * (MAX_TOKENS + 1));
	while (input && input[i] && i < MAX_TOKENS)
	{
		if (i == 0 || (input[i - 1] && (ft_strncmp(input[i - 1], "|", 1) == 0
					|| ft_strncmp(input[i - 1], "&", 1) == 0)))
			add_token(input[i], i, 1);
		else
			add_token(input[i], i, 0);
		i++;
	}
	term()->tokens[i] = NULL;
	i = 0;
	while (input && input[i] && i < MAX_TOKENS)
		free(input[i++]);
	if (input)
		free(input);
}
