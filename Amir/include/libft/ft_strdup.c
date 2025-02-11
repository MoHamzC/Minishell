/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 13:57:16 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:57:16 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s)
{
	size_t	l;
	size_t	i;
	char	*rs;

	if (!s)
		return (NULL);
	l = 0;
	i = 0;
	while (s[l])
		l++;
	rs = malloc(l + 1);
	if (!rs)
		return (NULL);
	while (s[i])
	{
		rs[i] = s[i];
		i++;
	}
	rs[i] = '\0';
	return (rs);
}
