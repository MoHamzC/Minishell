/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:37:42 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/13 20:14:56 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return;
	i = 0;
	while (tokens[i] && tokens[i]->value) 
    {
        free(tokens[i]->value);
        free(tokens[i]);
        i++;
    }
	free(tokens);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_token	**take_ur_token_and_leave_me_alone(t_env *env, char *line)
{
	t_token	**new_tokens;

	new_tokens = tokenize(line);
	if (post_tokenize(new_tokens, env) == 0)
	{
		free_tokens(new_tokens);
		return (0);
	}
	new_tokens = pre_process_redirections(new_tokens);
	return (new_tokens);
}
