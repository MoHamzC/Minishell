/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:22:59 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/21 18:30:41 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envlst_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_envlst_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_env	*create_env_node(char *env_str)
{
	char	*equal_sign;
	int		key_len;

	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
		return (NULL);
	key_len = equal_sign - env_str;
	return (ft_envlst_new(ft_substr(env_str, 0, key_len),
			ft_strdup(equal_sign + 1)));
}

t_env	*init_env(char **envp)
{
	t_env	*env_lst;
	t_env	*new;
	int		i;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		new = create_env_node(envp[i]);
		if (new)
			ft_envlst_add_back(&env_lst, new);
		i++;
	}
	return (env_lst);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
char	*builtin_get_envv(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}