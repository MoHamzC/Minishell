/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:37:42 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 05:57:37 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "minishell.h"

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
