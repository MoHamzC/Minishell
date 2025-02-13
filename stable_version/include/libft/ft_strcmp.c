/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:21:54 by calberti          #+#    #+#             */
/*   Updated: 2025/02/13 18:13:50 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s3;
	unsigned char	*s4;
	int i;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i=0;
	while ((s3[i] || s4[i]))
	{
		if (s3[i] < s4[i])
			return (s3[i] - s4[i]);
		if (s3[i] > s4[i])
			return (s3[i] - s4[i]);
		i ++;
	}
	return (0);
}