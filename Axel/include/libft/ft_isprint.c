/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:38 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 20:34:30 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c = 30;
	int	a = 44;
	j'ai envie de me suicid
	printf("%d", ft_isprintable(c));
	printf("%d", ft_isprintable(a));
}
*/
