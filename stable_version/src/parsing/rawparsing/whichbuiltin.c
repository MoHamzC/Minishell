/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whichbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:58:45 by mtarento          #+#    #+#             */
/*   Updated: 2025/02/26 19:36:26 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_rdir_tok(t_cmd_type type)
{
	return (type == REDIRIN || type == REDIROUT
		|| type == APPEND || type == HERE_DOC);
}

int	whichbuiltin(char *s)
{
	if (ft_strcmp(s, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(s, "cd") == 0)
		return (CD);
	else if (ft_strcmp(s, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(s, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(s, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(s, "env") == 0)
		return (ENV);
	else if (ft_strcmp(s, "exit") == 0)
		return (EXIT);
	else
		return (NOT_BUILTIN);
}

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
