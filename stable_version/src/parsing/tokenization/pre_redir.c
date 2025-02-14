/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:23:32 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 08:21:02 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_char(char *c)
{
	if (ft_strchr("<>", *c))
		return (1);
	return (0);
}

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
	while (tokens[i])
	{
		if (is_redir_token(tokens[i]->type) && is_redir_char(tokens[i]->value) && tokens[i]->quote == NO_QUOTE )
		{
			if (tokens[i + 1])
				tokens[i + 1]->type = tokens[i]->type;
			(free(tokens[i]->value),free(tokens[i]));
			i++;
		}
		else
			new_tokens[j++] = tokens[i++];
	}
	new_tokens[j] = NULL;
	return (free(tokens), new_tokens);
}
