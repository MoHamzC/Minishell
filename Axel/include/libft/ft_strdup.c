/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:16:41 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/19 14:54:29 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	size;

	size = ft_strlen(s);
	ptr = malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, size + 1);
	return (ptr);
}
/*
int     main(void)
{
        const char *s = "lalalala";
		char *ptr = ft_strdup(s);

		printf("%s\n", s);

		printf("%s", ft_strdup(s));
		
		printf("%s\n", ptr);
}
*/
