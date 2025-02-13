/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:36:19 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 05:42:39 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "minishell.h"

int	post_tokenize(t_token **tokens, t_env *env)
{
	assign_token_types(tokens);
	assign_quote_type(tokens);
	finalize_tokens(tokens, env);
	if (!check_pipe_errors(tokens))
		return (0);
	if (!check_redirection_errors(tokens))
		return (0);
	return (1);
}
