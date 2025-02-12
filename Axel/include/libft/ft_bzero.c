/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:29:33 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 13:41:06 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ps;

	ps = s;
	i = 0;
	while (i < n)
	{
		ps[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	char s[9] = "hhbjjh";

	printf("%s\n", s);

	ft_bzero(s, 3);

	printf("%s\n", s);
}
*/