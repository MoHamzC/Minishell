/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:56:26 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/13 20:09:01 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_update_env(t_env *envp, const char *key, const char new_value)
{
	while(envp->next)
	{
		if(strncmp(envp->key, key, strlen(key)) == 0)
		{
			free(envp->key);
			envp->value = ft_strdup(&new_value);
			return;
		}
		envp = envp->next;
	}
}
int ft_cd(t_env *envp)
{
	char *path;
	char *cwd;
	char *home;

	path = NULL;
	cwd = NULL;
	home = NULL;
	if(!path)
	{
		home = getenv("HOME");
		if(home == NULL)
		{
			write(2, "HOME not set\n", 14);
			return(-1) ;
		}
		path = home;
	}
	if(chdir(path) == -1)
	{
		perror("cd");
		return(-1);
	}
	printf("%s\n", path);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_update_env(envp, "PWD", *cwd);
	if (getenv("PWD"))
		ft_update_env(envp, "OLDPWD", *getenv("PWD"));
	return(0);
}
