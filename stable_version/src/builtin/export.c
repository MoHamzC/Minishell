/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:45:23 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/13 19:51:44 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"


// bool ift_is_valid_env_var(char *key)
// {
// 	int i;
// 	if (!key || !ft_isalpha(key[0]) && key[0] != '_')
// 		return false;
// 	i = 1;
// 	while(key[i] != '\0') 
// 	{
// 		if (!ft_isalnum(key[i]) && key[i] != '_')
// 			return false;
// 		i++;
// 	}
// 	return true;
// }
// void push_env_var(t_shell *shell, char *key, char *value) 
// {
// 	t_env *env = shell->env;
// 	while (env) 
// 	{
// 		if (strcmp(env->key, key) == 0) 
// 		{
//             free(env->value);
//             env->value = strdup(value);
//             return;
//         }
//         env = env->next;
//     }
    
//     // Si la variable n'existe pas, on l'ajoute
//     t_env *new_env = malloc(sizeof(t_env));
//     new_env->key = strdup(key);
//     new_env->value = strdup(value);
//     new_env->next = shell->env;
//     shell->env = new_env;
// }