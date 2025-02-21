/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_complex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:33:51 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/21 21:25:08 by mochamsa         ###   ########.fr       */
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

char	*extract_double_quote_segment(const char *token, int *i, t_shell *sh)
{
	int		start;
	char	*seg;
	char	*expanded;

	start = *i;
	while (token[*i] && token[*i] != '"')
		(*i)++;
	seg = ft_substr(token, start, *i - start);
	expanded = expand_variables(seg, sh);
	free(seg);
	return (expanded);
}

char	*extract_unquoted_segment(const char *token, int *i, t_shell *sh)
{
	int		start;
	char	*seg;
	char	*expanded;

	start = *i;
	while (token[*i] && token[*i] != '\'' && token[*i] != '"')
		(*i)++;
	seg = ft_substr(token, start, *i - start);
	expanded = expand_variables(seg, sh);
	free(seg);
	return (expanded);
}

char	*get_next_segment(char *token, int *i, t_shell *sh)
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
		segment = extract_double_quote_segment(token, i, sh);
		if (token[*i] == '"')
			(*i)++;
		return (segment);
	}
	else
		return (extract_unquoted_segment(token, i, sh));
}

char	*process_complex_token(char *token, t_shell *sh)
{
	char	*result;
	char	*part;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (token[i])
	{
		part = get_next_segment(token, &i, sh);
		tmp = result;
		result = ft_strjoin(result, part);
		free(tmp);
		free(part);
	}
	return (result);
}
