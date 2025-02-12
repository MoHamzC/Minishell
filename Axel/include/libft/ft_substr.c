/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:33:36 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/26 17:37:29 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	max_len;
	char	*ptr;

	if ((!s))
		return (NULL);
	if (start >= ft_strlen(s) || (ft_strlen(s) == 0))
	{
		ptr = ft_calloc(1, 1);
		return (ptr);
	}
	max_len = ft_strlen(s) - start;
	if (len > max_len)
		len = max_len;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
/*
int	main(void)
{
	char *s = "jjjjaaajjj";
	size_t len = 0;

	printf("%s", ft_substr(s, 5, len));
}
*/