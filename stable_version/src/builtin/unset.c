/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:35:45 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/13 20:09:30 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_key_compare(char *env_variable, char *key)
// {
// 	return(ft_strncmp(env_variable, key, ft_strlen(key)) == 0 
// 		&& env_variable[ft_strlen(key)] == '=');
// }
// void ft_del_env_var(char **envp, char *key)
// {
// 	t_env *current = *envp;
// 	t_env *previous = NULL;

// 	if(current && ft_key_compare(current->key, key))
// 	{
// 		*envp = current->next;
// 		free(current->key);
// 		free(current->value);
// 		free(current);
// 		return;
// 	}

// 	while(current->next)
// 	{
// 		if(ft_key_compare(current->key, key))
// 		{
// 			previous->next = current->next;
// 			free(current->key);
// 			free(current->value);
// 			free(current);
// 		return;
// 		}
// 	}
// 	previous = current;
// 	current = current->next;
// }

// int ft_unset(t_env *env, char **argv)
// {
// 	int i;

// 	i = 1;
// 	while(argv[i])
// 	{
// 		ft_del_env_var(argv[i], env);
// 		i++;
// 	}
// 	return(0);
// }