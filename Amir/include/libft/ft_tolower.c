/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 13:57:50 by mochamsa          #+#    #+#             */
/*   Updated: 2024/10/21 13:57:50 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

int	ft_tolower(int c)
{
	int	r;

	r = c;
	if (r >= 'A' && r <= 'Z')
		r += ('a' - 'A');
	return (r);
}
