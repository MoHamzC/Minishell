/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:13:40 by calberti          #+#    #+#             */
/*   Updated: 2025/02/24 16:53:25 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_cmd_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, cmd);
	free(tmp);
	return (result);
}

char	*find_command_path(char *cmd, char **env_paths)
{
	char	*cmd_path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (check_command_access(cmd) == 0)
			return (strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (env_paths && env_paths[i])
	{
		cmd_path = build_cmd_path(env_paths[i], cmd);
		if (check_command_access(cmd_path) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**get_path_dirs(char **env)
{
	char	*path_var;
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = env[i] + 5;
			return (ft_split(path_var, ':'));
		}
		i++;
	}
	return (NULL);
}

int	check_command_access(char *cmd_path)
{
	if (!cmd_path)
		return (-1);
	if (access(cmd_path, F_OK) != 0)
		return (-1);
	if (access(cmd_path, X_OK) != 0)
		return (-1);
	return (0);
}
