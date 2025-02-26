/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:45:23 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/26 21:28:43 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_and_free(char *key, char *value)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(key);
	free(value);
}

bool	ift_is_valid_env_var(char *key)
{
	int	i;

	if ((!key || !ft_isalpha(key[0])) && (key[0] != '_'))
		return (false);
	i = 1;
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	push_env_var(t_shell *shell, char *key, char *value)
{
	t_env	*env;
	t_env	*new_env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = shell->env;
	shell->env = new_env;
}

int	ft_export(char **args, t_shell *shell)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (j == (int)ft_strlen(args[i]))
			return (1);
		key = ft_substr(args[i], 0, j);
		value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
		if (ift_is_valid_env_var(key))
			push_env_var(shell, key, value);
		else
			return (error_and_free(key, value), 1);
		(free(key), free(value));
		i++;
	}
	return (0);
}
