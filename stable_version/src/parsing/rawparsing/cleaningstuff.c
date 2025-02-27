/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaningstuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:32:10 by mtarento          #+#    #+#             */
/*   Updated: 2025/02/27 04:16:50 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//not cleaning its for testing
t_token	*create_token(char *value, t_cmd_type type, t_word_type quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->type = type;
	token->quote = quote;
	return (token);
}

void	ft_free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	if (tokens == NULL)
		return ;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	frcm(t_command **command_ptr)
{
	t_command	*current;
	t_command	*next;

	current = *command_ptr;
	if (*command_ptr == NULL)
		return ;
	while (current)
	{
		next = current->next;
		ft_free_args(current->args);
		ft_free_redirs(current->redir);
		free(current);
		current = next;
	}
	*command_ptr = NULL;
}

void	ft_free_redirs(t_redir **redir)
{
	int	i;

	i = 0;
	if (!redir)
		return ;
	while (redir[i])
	{
		free(redir[i]->file);
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}
