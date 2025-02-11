/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:51:07 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:53:23 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	i;

	i = 0;
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	while (i < nmemb * size)
	{
		((unsigned char *)arr)[i] = '\0';
		i++;
	}
	return (arr);
}
