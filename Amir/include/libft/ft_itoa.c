/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 13:55:44 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:55:44 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*allocate_result(int size)
{
	char	*reslt;

	reslt = (char *)malloc(size + 1);
	if (reslt == NULL)
		return (NULL);
	reslt[size] = '\0';
	return (reslt);
}

int	get_size_and_sign(int n, int *sign)
{
	long	s;
	int		size;

	s = n;
	size = 0;
	*sign = 1;
	if (s < 0)
	{
		size = 1;
		*sign = -1;
		s *= -1;
	}
	while (s > 0)
	{
		s /= 10;
		size++;
	}
	if (size == 0)
		size++;
	return (size);
}

void	fill_result(char *reslt, long s, int size, int sign)
{
	while (size > 0)
	{
		reslt[size - 1] = s % 10 + '0';
		s /= 10;
		size--;
	}
	if (sign == -1)
		reslt[0] = '-';
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	long	s;
	char	*reslt;

	size = get_size_and_sign(n, &sign);
	reslt = allocate_result(size);
	if (reslt == NULL)
		return (NULL);
	s = (long)n * sign;
	fill_result(reslt, s, size, sign);
	return (reslt);
}
