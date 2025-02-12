/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:06:00 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/19 16:19:50 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ps;
	unsigned int	i;

	ps = s;
	i = 0;
	while (i < n)
	{
		ps[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
/*
int main(void)
{
	printf("%s\n", s);
		
	mem	et(s, c, n);
		
	printf("%s\n", s);
}
*/