/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:25:09 by axburin-          #+#    #+#             */
/*   Updated: 2025/01/16 13:39:17 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_worlds(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			++i;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			++i;
	}
	return (count);
}

static void	free_table(char **pptr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(pptr[i]);
		++i;
	}
	free(pptr);
}

char	**ft_split(const char *s, char c)
{
	char	**pptr;
	size_t	i;
	size_t	j;
	size_t	end;

	pptr = malloc(sizeof(char *) * (ft_count_worlds(s, c) + 1));
	if (!pptr)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_count_worlds(s, c))
	{
		while (s[i] && s[i] == c)
			++i;
		end = 0;
		while (s[i + end] != '\0' && s[i + end] != c)
			++end;
		pptr[j++] = ft_substr(s + i, 0, end);
		if (!pptr[j - 1])
			return (free_table(pptr, j - 1), NULL);
		i += end;
	}
	pptr[j] = NULL;
	return (pptr);
}
/*
int main (void)
{
	char *str = "...hello...word...!!!";
	char c = '.';
	char **res = ft_split(str,c);
	printf("%s", res[0]);
	printf("%s", res[1]);
	printf("%s", res[2]);
	printf("%s", res[3]);

}
*/