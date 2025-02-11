/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 13:56:40 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:56:40 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ms1;
	unsigned char	*ms2;

	if (!dest && !src)
		return ("");
	ms1 = (unsigned char *)dest;
	ms2 = (unsigned char *)src;
	while (n > 0)
	{
		*ms1 = *ms2;
		ms1++;
		ms2++;
		n--;
	}
	return (dest);
}
