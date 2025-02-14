/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:30:51 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/14 02:06:44 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_arg(int argc, char **argv, int nl)
{
	int i;

	i = 0;
	while(i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if(i < argc -1)
			write(1, " ", 1);
		i++;
	}
	if(nl)
		write(1, "\n", 1);
}

int ft_echo(int argc, char **argv)
{
	int nl;
	int i;

	i = 2;
	nl = 1;
	if(argc > 1 && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		nl = 0;
		i++;
	}
	ft_print_arg(argc - i, &argv[i], nl);
	return(0);
}
