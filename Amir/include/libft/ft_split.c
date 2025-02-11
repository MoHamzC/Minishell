/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 13:57:05 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:57:05 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

size_t	ft_strlen(const char *s);

int	is_sep(char c, char delimiter)
{
	return (c == delimiter);
}

int	count_words(const char *str, char delimiter)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_sep(*str, delimiter) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_sep(*str, delimiter))
			in_word = 0;
		str++;
	}
	return (count);
}

char	*add_str(const char *str, int *start, int finish)
{
	char	*mstr;
	int		s;
	int		i;

	s = *start;
	mstr = malloc((finish - s + 1) * sizeof(char));
	if (!mstr)
		return (NULL);
	i = 0;
	while (s < finish)
		mstr[i++] = str[s++];
	mstr[i] = '\0';
	*start = -1;
	return (mstr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (!is_sep(s[i], c) && index < 0)
			index = i;
		else if ((is_sep(s[i], c) || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = add_str(s, &index, i);
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
