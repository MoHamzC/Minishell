/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:44:53 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/23 17:28:16 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

void	assign_token_types(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i]->type = wich_type(tokens[i]->value);
		i++;
	}
}

void	assign_quote_type(t_token **tokens)
{
	int	i;
	int	len;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->value)
		{
			len = ft_strlen(tokens[i]->value);
			if (len >= 2 && tokens[i]->value[0] == '\''
				&& tokens[i]->value[len - 1] == '\'')
				tokens[i]->quote = SINGLE_QUOTE;
			else if (len >= 2 && tokens[i]->value[0] == '\"'
				&& tokens[i]->value[len - 1] == '\"')
				tokens[i]->quote = DOUBLE_QUOTE;
			else
				tokens[i]->quote = NO_QUOTE;
		}
		else
			tokens[i]->quote = NO_QUOTE;
		i++;
	}
}

int	finalize_tokens(t_token **tokens, t_shell *sh)
{
	char	*tmp;
	int		i;

	i = 0;
	while (tokens[i])
	{
		tmp = tokens[i]->value;
		tokens[i]->value = process_complex_token(tmp, sh);
		if (ft_strcmp(tmp, tokens[i]->value) != 0)
			tokens[i]->quote = SINGLE_QUOTE;
		free(tmp);
		i++;
	}
	return (1);
}

int	check_pipe_errors(t_token **tokens)
{
	int	i;

	i = 0;
	if (tokens[0] && tokens[0]->type == PIPE)
	{
		ft_putstr_fd("Syntax error: pipe en debut de commande\n", 2);
		return (0);
	}
	while (tokens[i])
	{
		if (tokens[i]->type == PIPE)
		{
			if (!tokens[i + 1] || tokens[i + 1]->type == PIPE)
			{
				ft_putstr_fd("Syntax error: pipe mal place\n", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_redirection_errors(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redir_token(tokens[i]->type) && three_redir(tokens[i]->value))
			return (ft_putstr_fd("Syntax error: trop de redirections\n", 2), 0);
		if (is_redir_token(tokens[i]->type))
		{
			if (!tokens[i + 1] || tokens[i + 1]->type != WORD)
				return (ft_putstr_fd("Syntax error: redirection mal forme\n",
						2), 0);
		}
		i++;
	}
	return (1);
}
