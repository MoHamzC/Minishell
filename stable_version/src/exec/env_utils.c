/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:37:57 by calberti          #+#    #+#             */
/*   Updated: 2025/02/26 21:57:49 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_size(t_env *env)
{
	int		size;
	t_env	*current;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	*create_env_string(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**env_list_to_array(t_env *env)
{
	char	**arr;
	t_env	*current;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		arr[i] = create_env_string(current->key, current->value);
		if (!arr[i])
		{
			free_env_array(&arr);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_env_array(char ***env_arr_ptr)
{
	char	**env_arr;
	int		i;

	env_arr = *env_arr_ptr;
	i = 0;
	if (!env_arr)
		return ;
	while (env_arr[i])
	{
		free(env_arr[i]);
		env_arr[i] = NULL;
		i++;
	}
	free(env_arr);
	*env_arr_ptr = NULL;
}
