/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:23:32 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/23 18:17:13 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"

int	is_redir_token(t_cmd_type type)
{
	return (type == REDIRIN || type == REDIROUT
		|| type == APPEND || type == HERE_DOC);
}

int	count_tokens_total(t_token **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

int	count_redir_tokens(t_token **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (is_redir_token(tokens[i]->type))
			count++;
		i++;
	}
	return (count);
}

t_token	*copy_token(t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	new_token->type = token->type;
	new_token->quote = token->quote;
	new_token->value = ft_strdup(token->value);
	return (new_token);
}

t_token	**pre_process_redirections(t_token **tokens)
{
	int		new_count;
	int		i;
	int		j;
	t_token	**new_tokens;

	i = 0;
	j = 0;
	new_count = count_tokens_total(tokens) - count_redir_tokens(tokens);
	new_tokens = malloc(sizeof(t_token *) * (new_count + 1));
	while (j < new_count)
	{
		if (is_redir_token(tokens[i]->type) && is_redir_char(tokens[i]->value)
			&& tokens[i]->quote == NO_QUOTE)
		{
			if (tokens[i + 1])
				tokens[i + 1]->type = tokens[i]->type;
			i++;
		}
		else
			new_tokens[j++] = copy_token(tokens[i++]);
	}
	new_tokens[j] = NULL;
	return (free_tokens(tokens), new_tokens);
}
