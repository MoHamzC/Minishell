/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaningstuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:32:10 by mtarento          #+#    #+#             */
/*   Updated: 2025/02/22 21:53:05 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void ft_free_redirs(t_redir **redir)
{
	int i; 
	i = 0; 
	if(redir)
	{
	free(redir[i]->file);
	free(redir[i]); 
	i++; 
	}
	free(redir); 
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void ft_free_commands(t_command *command)
{
	t_command *current; 
	t_command *next; 

	current = command; 
	while(current)
	{
		next = current->next; 
		ft_free_args(current->args); 
		ft_free_redirs(current->redir); 
		free(current); 
	}
}
