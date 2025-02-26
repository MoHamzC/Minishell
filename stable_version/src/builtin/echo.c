/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:30:51 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/26 14:56:09 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_arg(int argc, char **argv, int nl)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i < argc -1)
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
}

int	check_nl(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(int argc, char **argv)
{
	int	nl;
	int	i;

	i = 1;
	nl = 1;
	while (argc > 1 && argv[i] && check_nl(argv[i]) == 0)
	{
		nl = 0;
		i++;
	}
	ft_print_arg(argc - i, &argv[i], nl);
	return (0);
}
