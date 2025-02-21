/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:35:45 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/21 17:26:21 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_key_compare(char *env_variable, char *key)
{
	return(ft_strncmp(env_variable, key, ft_strlen(key)) == 0 
		&& env_variable[ft_strlen(key)] == '=');
}
void ft_del_env_var(t_env *envp, char *key)
{
	t_env *current = envp;
	t_env *previous = NULL;

	if(current && ft_key_compare(current->key, key))
	{
		envp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return;
	}

	while(current->next)
	{
		if(ft_key_compare(current->key, key))
		{
			previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
		return;
		}
	}
	previous = current;
	current = current->next;
}

int ft_unset(t_env *env, char **args)
{
    int i;

    i = 1;
    while(args[i])
    {
        ft_del_env_var(env, args[i]);
        i++;
    }
    return 0;
}