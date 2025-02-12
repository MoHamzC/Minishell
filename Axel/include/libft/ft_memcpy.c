/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:57:53 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/21 08:53:39 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char		*psrc;
	size_t			i;
	char			*pdst;

	if (!dest && !src)
		return ("");
	pdst = dest;
	psrc = src;
	i = 0;
	while ((i < n))
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (pdst);
}
/*
int main(void)
{
    unsigned int dest [] = {0,1,2,3,4,5,6,7};
	const int src[] = {8,9};
	size_t n = 2;
    unsigned int i;
    ft_memcpy(dest, src, n);
    
    i = 0;
    while( i < 8)
    {
        printf("%d", (*dest)++);
        i++;
    }    
}
*/
