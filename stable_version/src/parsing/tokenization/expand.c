/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:54:26 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 14:55:25 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

char	*get_envv(t_env *env, char *key)
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
	if (j == *i && str[j] == '$')
	{
		*i = j + 1;
		return (ft_strdup(" "));
	}
	if ((j == *i && !str[*i]) || (str[j] == '$' && str[j + 1] == '\'' && str[j + 1] == '"'))
		return (ft_strdup(""));
	var = ft_substr(str, *i, j - *i);
	expansion = ft_strdup(get_envv(env, var));
	*i = j;
	return (free(var), expansion);
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
		if (str[i] == '$' && str[i + 1])
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
