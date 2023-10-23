/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:53:12 by anlima            #+#    #+#             */
/*   Updated: 2023/10/19 22:56:03 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokenize_input(void);
int		count_words(char *input);
void	add_token(char *input, int *i, int flag);
void	set_token_type(t_token *token, char *input, int flag);
void	add_tokens_from_command(char *command, int *token_index);

void	tokenize_input(void)
{
	int		i;
	int		token_index;
	char	**input;

	input = ft_split_pipes(term()->command);
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

	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] != ' ' && (i == 0 || quote == 0))
			j++;
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i++;
	}
	return (j);
}

void	add_token(char *input, int *i, int flag)
{
	t_token	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(t_token));
	set_token_type(token, input, flag);
	if ((token->type == RED_IN || token->type == RED_OUT) && input[1] != ' '
		&& input[1] != '\0')
		j = 1;
	else if ((token->type == APPEND || token->type == HEREDOC)
		&& input[2] != ' ' && input[2] != '\0')
		j = 2;
	if (j > 0)
		token->value = ft_substr(input, 0, j);
	else
		token->value = ft_substr(input, 0, ft_strlen(input));
	term()->tokens[(*i)] = token;
	// printf("DEBUG: value => %s\ttype => %i\n", token->value, token->type);
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

	temp = split_command(command);
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

void	set_token_type(t_token *token, char *input, int flag)
{
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
	else
		token->type = ARG;
}
