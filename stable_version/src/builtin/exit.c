/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:12:54 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/23 13:56:17 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_numeric(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(int argc, char **argv, t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	if (argc > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		shell->exit_status = 1;
		return (-1);
	}
	if (argc == 2)
	{
		if (!ft_is_numeric(argv[1]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit_status = 2;
			(free(shell), exit(exit_status));
		}
		exit_status = atoi(argv[1]);
	}
	if (exit_status < 0)
		exit_status += 256;
	exit_status %= 256;
	printf("exit\n");
	exit(exit_status);
}
