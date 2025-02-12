/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:00:41 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/19 16:02:26 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*last_occu;
	size_t		i;

	last_occu = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			last_occu = (char *) s + i;
		i++;
	}
	if (s[i] == (char)c && !last_occu)
		return ((char *)(s + i));
	return (last_occu);
}
/*
int main(void)
{
//    char s[] = ;
//  int c = '\0';
//    char * res = ft_strrchr(s,c);
//   printf("%s", res);
}
*/
