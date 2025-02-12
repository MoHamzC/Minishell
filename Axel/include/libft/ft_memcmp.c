/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:02:13 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 13:38:35 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		i;
	unsigned char		*s1_cpy;
	unsigned char		*s2_cpy;

	s1_cpy = (unsigned char *) s1;
	s2_cpy = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1_cpy[i] != s2_cpy[i])
			return (s1_cpy[i] - s2_cpy[i]);
		i++;
	}
	return (0);
}
/*
int main(void)
{
    char *s2 = "\xff\0\0\xaa\0\xde\x00MBS";
    char *s1 = "\xff\0\0\xaa\0\xde\xffMACOSX\xff";
    size_t n = 9;

    printf("%d", ft_memcmp(s1, s2, n));
}
*/
