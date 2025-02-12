/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 07:46:39 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/26 17:34:01 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char s, char const *set)
{
	while (*set)
	{
		if (*set == s)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*ptr;
	size_t			size;
	int				i;
	int				j;

	i = 0;
	while (ft_check(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && ft_check(s1[j], set))
		j--;
	size = (j - i) + 1;
	if (j < i)
		return (ft_strdup(""));
	ptr = ft_substr(s1, i, size);
	return (ptr);
}
/*
 int main(void)
 {
	char const s1 ="abcbbc";
	char const s2 = "b";

	
 }
 */