/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:42:02 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/24 15:41:13 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *envp)
{
	char	*s;

	(void)envp;
	s = NULL;
	s = getcwd(s, 0);
	if (!s)
		perror("pwd");
	if (s)
	{
		printf("%s\n", s);
		free(s);
	}
	return (0);
}
