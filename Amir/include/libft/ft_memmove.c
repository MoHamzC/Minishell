/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 13:56:44 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:56:44 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ms1;
	const unsigned char	*ms2;

	ms1 = (unsigned char *)dest;
	ms2 = (const unsigned char *)src;
	if (ms1 < ms2)
	{
		while (n--)
		{
			*ms1++ = *ms2++;
		}
	}
	else if (ms1 > ms2)
	{
		ms1 += n;
		ms2 += n;
		while (n--)
		{
			*(--ms1) = *(--ms2);
		}
	}
	return (dest);
}
