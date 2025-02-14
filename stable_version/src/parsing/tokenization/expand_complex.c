/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_complex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:33:51 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 14:55:32 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "minishell.h"

char	*extract_single_quote_segment(const char *token, int *i)
{
	int	start;

	start = *i;
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	return (ft_substr(token, start, *i - start));
}

char	*extract_double_quote_segment(const char *token, int *i, t_env *env)
{
	int		start;
	char	*seg;
	char	*expanded;

	start = *i;
	while (token[*i] && token[*i] != '"')
		(*i)++;
	seg = ft_substr(token, start, *i - start);
	expanded = expand_variables(seg, env);
	free(seg);
	return (expanded);
}

char	*extract_unquoted_segment(const char *token, int *i, t_env *env)
{
	int		start;
	char	*seg;
	char	*expanded;

	start = *i;
	while (token[*i] && token[*i] != '\'' && token[*i] != '"')
		(*i)++;
	seg = ft_substr(token, start, *i - start);
	expanded = expand_variables(seg, env);
	free(seg);
	return (expanded);
}

char	*get_next_segment(char *token, int *i, t_env *env)
{
	char	*segment;

	if (token[*i] == '\'')
	{
		(*i)++;
		segment = extract_single_quote_segment(token, i);
		if (token[*i] == '\'')
			(*i)++;
		return (segment);
	}
	else if (token[*i] == '"')
	{
		(*i)++;
		segment = extract_double_quote_segment(token, i, env);
		if (token[*i] == '"')
			(*i)++;
		return (segment);
	}
	else
		return (extract_unquoted_segment(token, i, env));
}

char	*process_complex_token(char *token, t_env *env)
{
	char	*result;
	char	*part;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (token[i])
	{
		part = get_next_segment(token, &i, env);
		tmp = result;
		result = ft_strjoin(result, part);
		free(tmp);
		free(part);
	}
	return (result);
}
