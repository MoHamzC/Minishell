/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:26:46 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 13:40:12 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z' ) || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	int	c = 'a';
	int	C = 2;

	printf("%d", ft_isalpha(c));
	 printf("%d", ft_isalpha(C));
}
*/