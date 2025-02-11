/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 13:56:37 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:56:37 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ms1;
	unsigned char	*ms2;

	ms1 = (unsigned char *)s1;
	ms2 = (unsigned char *)s2;
	while (n > 0 && *ms1 == *ms2)
	{
		ms1++;
		ms2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*ms1 - *ms2);
}
