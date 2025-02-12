/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:27:37 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/21 17:52:43 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calcul_size(long nb)
{
	unsigned int	size;

	size = 0;
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	if (nb == 0)
		size++;
	if (nb > 0)
	{
		while (nb)
		{
			nb = nb / 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		is_negative;
	size_t	size;
	long	nb;
	char	*ptr;

	nb = (long) n;
	size = calcul_size(nb);
	is_negative = 0;
	ptr = malloc ((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		ptr[0] = '-';
		is_negative = 1;
	}
	while (size > (size_t) is_negative)
	{
		ptr[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	ptr[calcul_size(n)] = '\0';
	return (ptr);
}
/*
int	main (void)
{
	char *res = ft_itoa(433);
	if(res != NULL)
	{
	printf("%d", calcul_size(001));

	printf("%s",ft_itoa(65464651646874));
	}
	return(0);
}
*/