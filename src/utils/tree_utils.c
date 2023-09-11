/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:51:15 by anlima            #+#    #+#             */
/*   Updated: 2023/09/11 17:11:25 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		free_commands(t_command *root);
void		print_commands(t_command *root);
t_command	*create_command_node(char *command);
void		insert_node(t_command **root, char *command);

void	free_commands(t_command *root)
{
	if (root)
	{
		free_commands(root->left);
		free_commands(root->right);
		free(root);
	}
}

void	print_commands(t_command *root)
{
	if (root != NULL)
	{
		print_commands(root->left);
		printf("%s\n", root->command);
		print_commands(root->right);
	}
}

t_command	*create_command_node(char *command)
{
	t_command	*node;

	node = (t_command *)malloc(sizeof(t_command));
	if (node)
	{
		node->command = command;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

void	insert_node(t_command **root, char *command)
{
	if (*root == NULL)
		*root = create_command_node(ft_strdup(command));
	else
	{
		if (is_valid_red(&command, 0))
			insert_node(&(*root)->left, command);
		else
			insert_node(&(*root)->right, command);
	}
}
