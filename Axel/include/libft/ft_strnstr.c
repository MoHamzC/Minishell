/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:28:35 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 14:22:35 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (*little == '\0')
		return ((char *) big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (little[0] == big[i])
		{
			j = 0;
			while (little[j] == big[i + j] && little[j] != '\0'
				&& big[i + j] != '\0' && (i + j) < len)
			{
				j++;
			}
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	// const char big[] = "lorem ipsum dolor sit amet";
	// const char little[] = "ipsum";
	// size_t len = 15;

	printf("%s", ft_strnstr("lorem ipsum dolor sit amet little", "ipsum", 15));
}
*/
