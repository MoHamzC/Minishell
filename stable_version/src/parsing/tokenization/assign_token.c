/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:36:19 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 08:21:37 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "minishell.h"

int three_redir(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			count++;
		if (count >= 3)
			return (1);
		i++;
	}
	return (0);
}
int	check_quotes(const char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote == 0);
}

int	post_tokenize(t_token **tokens, t_env *env)
{
	assign_token_types(tokens);
	assign_quote_type(tokens);
	if (!check_pipe_errors(tokens))
		return (0);
	if (!check_redirection_errors(tokens))
		return (0);
	finalize_tokens(tokens, env);
	return (1);
}
