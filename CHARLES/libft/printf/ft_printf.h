/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:17:14 by calberti          #+#    #+#             */
/*   Updated: 2024/10/30 19:17:19 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_isformat(char c);
int	ft_format(va_list *args, char c);
int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_strlen(char *str);
int	ft_putnbr(int nb);
int	ft_putnbrui(unsigned int nb);
int	ft_hexa(unsigned int nb, char c);
int	ft_ptr(unsigned long int nb);

#endif
