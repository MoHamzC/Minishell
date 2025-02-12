/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:54:26 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 06:10:44 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*append_char(char *s, char c)
{
	char	tmp[2];
	char	*res;

	tmp[0] = c;
	tmp[1] = '\0';
	res = ft_strjoin(s, tmp);
	free(s);
	return (res);
}

char	*handle_dollar(char *str, int *i, t_env *env)
{
	int		j;
	char	*var;
	char	*expansion;

	j = *i;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var = ft_substr(str, *i, j - *i);
	expansion = ft_strdup(get_env_value(env, var));
	free(var);
	*i = j;
	return (expansion);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*tmp;
	int		i;
	char	*expansion;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			tmp = result;
			expansion = handle_dollar(str, &i, env);
			result = ft_strjoin(result, expansion);
			free(expansion);
			free(tmp);
		}
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}
