/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:53:12 by anlima            #+#    #+#             */
/*   Updated: 2023/10/16 16:18:14 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokenize_input(void);
int		count_words(char *input);
int		handle_red(char *input, int *i);
void	add_token(char *input, int *i, int flag);
void	add_tokens_from_command(char *command, int *token_index);

void	tokenize_input(void)
{
	int		i;
	int		token_index;
	char	**input;

	input = ft_split(term()->command, '|');
	i = 0;
	token_index = 0;
	term()->tokens = (t_token **)malloc(sizeof(t_token *) * (MAX_TOKENS + 1));
	while (input && input[i] && i < MAX_TOKENS)
	{
		add_tokens_from_command(input[i], &token_index);
		i++;
	}
	term()->tokens[token_index] = NULL;
}

int	count_words(char *input)
{
	int	i;
	int	j;
	int	quote;

	i = 4;
	j = 0;
	quote = 0;
	while (input[++i])
	{
		if (input[i] == ' ' && quote == 0)
		{
			while (input[i] == ' ' && quote == 0)
				i++;
			if (input[i] != '\0')
				j++;
			else
				break ;
		}
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
	}
	return (j);
}

void	add_token(char *input, int *i, int flag)
{
	int		j;
	t_token	*token;

	j = 0;
	token = malloc(sizeof(t_token));
	if (ft_strncmp(input, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(input, "<<", 2) == 0)
		token->type = HEREDOC;
	else if (input[0] == '<')
		token->type = RED_IN;
	else if (input[0] == '>')
		token->type = RED_OUT;
	else if (flag || ft_strncmp(input, "$?", 2) == 0)
		token->type = CMD;
	else if (input[0] == '|' || input[0] == '&')
		token->type = PIPE;
	else if (input[0] == '$' || (input[0] == '"' && input[1] == '$'))
		token->type = VAR;
	else
		token->type = ARG;
	if ((token->type == RED_IN || token->type == RED_OUT) && (input[1] != ' '
			&& input[1] != '\0'))
	{
		j = 1;
		token->value = ft_substr(input, 0, 1);
	}
	else if ((token->type == APPEND || token->type == HEREDOC)
		&& (input[2] != ' ' && input[1] != '\0'))
	{
		j = 2;
		token->value = ft_substr(input, 0, 2);
	}
	else
		token->value = ft_strdup(input);
	term()->tokens[*i] = token;
	if (j > 0)
	{
		(*i)++;
		add_token(&input[j], i, 0);
	}
}

void	add_tokens_from_command(char *command, int *token_index)
{
	int		j;
	char	**temp;

	temp = NULL;
	if (ft_strncmp(command, "echo ", 5) == 0)
		temp = treat_echo(command);
	else
		temp = ft_split(command, ' ');
	j = -1;
	while (temp && temp[++j] && *token_index < MAX_TOKENS)
	{
		if (j == 0)
			add_token(temp[j], token_index, 1);
		else
			add_token(temp[j], token_index, 0);
		(*token_index)++;
	}
}
