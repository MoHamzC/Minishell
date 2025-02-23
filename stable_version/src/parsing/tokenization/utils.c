/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:37:42 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/23 18:17:20 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->value)
			free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	show_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("token[%d] = %s type = %d quote = %d\n", i, tokens[i]->value,
			tokens[i]->type, tokens[i]->quote);
		i++;
	}
}

void	skip_quotes(const char *str, char **res, size_t *i, size_t *j)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		quote = str[*i];
		(*res)[(*j)++] = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			(*res)[(*j)++] = str[(*i)++];
		if (str[*i] == quote)
			(*res)[(*j)++] = str[(*i)++];
	}
}

int	skip_quotes_syntax(const char *str)
{
	char	quote;
	int		i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
		if (str[i] == quote)
			i++;
	}
	return (i);
}

t_token	**take_ur_token_and_leave_me_alone(char *line, t_shell *sh)
{
	t_token	**new_tokens;
	char	*new_line;

	if (check_quotes(line) == 0)
	{
		sh->exit_status = 2;
		return (printf("error: quotes\n"), NULL);
	}
	new_line = add_spaces_around_specials(line);
	new_tokens = tokenize(new_line);
	free(new_line);
	if (post_tokenize(new_tokens, sh) == 0)
		return (free_tokens(new_tokens), NULL);
	new_tokens = pre_process_redirections(new_tokens);
	return (new_tokens);
}
