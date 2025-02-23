/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 03:51:25 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/23 17:37:07 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*alloc_result(const char *input)
{
	size_t	len;
	char	*res;

	len = strlen(input);
	res = malloc(3 * len + 1);
	return (res);
}

size_t	process_double_token(const char *input, size_t i, char *res,
		size_t j)
{
	if (j && res[j - 1] != ' ')
		res[j++] = ' ';
	res[j++] = input[i];
	res[j++] = input[i + 1];
	if (input[i + 2] && input[i + 2] != ' ')
		res[j++] = ' ';
	return (j);
}

size_t	process_single_token(const char *input, size_t i, char *res,
		size_t j)
{
	if (j && res[j - 1] != ' ')
		res[j++] = ' ';
	res[j++] = input[i];
	if (input[i + 1] && input[i + 1] != ' ')
		res[j++] = ' ';
	return (j);
}

char	*add_spaces_around_specials(char *input)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = alloc_result(input);
	while (input[i])
	{
		skip_quotes(input, &res, &i, &j);
		if (input[i] && (input[i] == '<' || input[i] == '>')
			&& input[i + 1] == input[i])
		{
			j = process_double_token(input, i, res, j);
			i += 2;
		}
		else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			j = process_single_token(input, i++, res, j);
		else if (input[i])
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}
