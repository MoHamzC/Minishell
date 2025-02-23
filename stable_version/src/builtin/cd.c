/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:58:00 by axburin-          #+#    #+#             */
/*   Updated: 2025/02/23 15:48:38 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_env(t_env *envp, const char *key, const char *new_value)
{
	while (envp->next)
	{
		if (ft_strncmp(envp->key, key, ft_strlen(key)) == 0)
		{
			free(envp->value);
			envp->value = ft_strdup(new_value);
			return ;
		}
		envp = envp->next;
	}
}

int	change_to_home(t_shell *shell)
{
	char	*home;

	home = builtin_get_envv(shell->env, "HOME");
	if (!home)
	{
		write(2, "HOME not set\n", 14);
		return (-1);
	}
	if (chdir(home) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(home);
		return (-1);
	}
	return (0);
}

int	change_directory(t_shell *shell, char *path)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (-1);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		ft_update_env(shell->env, "PWD", cwd);
	if (getenv("PWD"))
		ft_update_env(shell->env, "OLDPWD", getenv("PWD"));
	return (0);
}

int	ft_cd(t_shell *shell)
{
	int	size;

	size = 0;
	while (shell->cmds->args[size])
		size++;
	if (size > 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->cmds->args[0], 2);
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (size == 1 || !shell->cmds->args[1])
		return (change_to_home(shell));
	return (change_directory(shell, shell->cmds->args[1]));
}
