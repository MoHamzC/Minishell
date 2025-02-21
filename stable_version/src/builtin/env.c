/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:46:07 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/21 17:28:24 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_env *envp)
{
	t_env *env = envp;
	while(env)
	{
		printf("%s=%s\n", env->key,env->value);
		env = env->next;
	}
	return(0);
}

//marche pas
