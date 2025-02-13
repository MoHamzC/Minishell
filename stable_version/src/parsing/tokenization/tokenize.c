/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:49 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 05:48:46 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static int	skip_token(char *line, int i)
{
	char	quote;

	while (line[i] && !ft_isspace(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

int	count_tokens(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i])
		{
			count++;
			i = skip_token(line, i);
		}
	}
	return (count);
}

char	*extract_token(char **line)
{
	int		start;
	int		end;
	char	*str;
	char	*token;

	str = *line;
	start = 0;
	while (str[start] && ft_isspace(str[start]))
		start++;
	end = skip_token(str, start);
	token = ft_substr(str, start, end - start);
	if (!token)
		return (NULL);
	*line = &str[end];
	return (token);
}

int	wich_type(char *token)
{
	if (ft_strncmp(token, ">", 2) == 0)
		return (REDIROUT);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<", 2) == 0)
		return (REDIRIN);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HERE_DOC);
	if (ft_strncmp(token, "|", 2) == 0)
		return (PIPE);
	return (WORD);
}

t_token	**tokenize(char *line)
{
	t_token	**tokens;
	int		nb_tokens;
	int		j;
	char	*current;

	nb_tokens = count_tokens(line);
	tokens = malloc(sizeof(t_token *) * (nb_tokens + 1));
	j = 0;
	current = line;
	while (*current)
	{
		while (*current && ft_isspace(*current))
			current++;
		if (*current)
		{
			tokens[j] = malloc(sizeof(t_token));
			tokens[j]->value = extract_token(&current);
			if (!tokens[j])
				return (free_tokens(tokens), NULL);
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}
