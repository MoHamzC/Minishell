/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:14:04 by calberti          #+#    #+#             */
/*   Updated: 2025/02/11 18:34:59 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_ptr(unsigned long int nb)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += ft_ptr(nb / 16);
	if (nb % 16 <= 9)
		len += ft_putchar((nb % 16) + '0');
	else
		len += ft_putchar((nb % 16) + 87);
	return (len);
}
/*
#include <stdio.h>

int main()
{

	int nb = 1234;
	int len;
	len = ft_ptr(nb);
	printf("\n%d\n", len);

	return 0;
}

Un pointeur est une variable qui stocke une adresse mémoire.
Cette adresse est représentée par un entier non signé
(généralement exprimé en hexadécimal).
 si nb % 16 <= a 9 on met juste le chiffre
 si il est > on fait plus 87 pour passer de 13 (13) a d (100)
*/
