/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:42:02 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/12 10:59:46 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(t_env *envp)
{
	char *s;

	s = NULL;
	while(envp->next)
	{
		if(ft_strncmp(envp->key, "PWD", 3) == 0)
		{
			s = ft_strdup(envp->value);
			break;
		}
		envp = envp->next;
	}
	printf("%s\n", s);
	free(s);
}