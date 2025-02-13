/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:13:34 by calberti          #+#    #+#             */
/*   Updated: 2025/02/11 18:34:59 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, format);
	i = 0;
	len = 0;
	if (!format)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && ft_isformat(format[i + 1]) == 1)
		{
			len += ft_format(&args, format[i + 1]);
			i++;
		}
		else
			len += ft_putchar(format[i]);
		i++;
		if (len == -1)
			return (len);
	}
	va_end(args);
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	char c = 'D';
	int nb = 42;
	char *str = "salut";
	int *ptr = &nb;
	unsigned int ui= 123456;
	int hex = 1234;
	
	ft_printf("Mine : %c \n", c);
	printf("Real : %c \n", c);
    
	ft_printf("Mine : %s \n", str);
	printf("Real : %s \n", str);
    
	ft_printf("Mine : %p \n", ptr);
	printf("Real : %p \n", ptr);
    
	ft_printf("Mine : %d \n", nb);
	printf("Real : %d \n", nb);
    
	ft_printf("Mine : %i \n", nb);
	printf("Real : %i \n", nb);
    
	ft_printf("Mine : %u \n", ui);
	printf("Real : %u \n", ui);
    
	ft_printf("Mine : %x \n", hex);
	printf("Real : %x \n", hex);
    
	ft_printf("Mine : %X \n", hex);
	printf("Real : %X \n", hex);
    
	ft_printf("Mine : %% \n");
	printf("Real : %% \n");
	return (0);
}
*/
