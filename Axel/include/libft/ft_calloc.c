/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:20:24 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 13:40:51 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned int	i;
	void			*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((unsigned char *) ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
/*
int main(void)
{        
	printf("%p", ft_calloc(0, 0));
}
*/