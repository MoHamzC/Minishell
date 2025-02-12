/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:52:36 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 13:38:45 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*s_cpy;
	size_t				i;

	s_cpy = ((unsigned char *) s);
	i = 0;
	while (i < n)
	{
		if (*s_cpy == (unsigned char)c)
			return ((void *) s_cpy);
		s_cpy++;
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char s[] = "aaaaabaaa";
	int c = 'b';
	size_t n = 7;
	char * res = ft_memchr(s, c, n);
    printf("%s", res);
}
*/
