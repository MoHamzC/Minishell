/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:13 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:53:27 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s_cpy;

	i = 0;
	s_cpy = (unsigned char *)s;
	while (i < n)
	{
		s_cpy[i] = '\0';
		i++;
	}
}
