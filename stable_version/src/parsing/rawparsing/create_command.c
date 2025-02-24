/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:58:17 by mtarento          #+#    #+#             */
/*   Updated: 2025/02/25 23:26:58 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//on ajoute une nouvlle commande on set tout a null
t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->redir = NULL;
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->builtin_value = NOT_BUILTIN;
	cmd->next = NULL;
	return (cmd);
}

//on ajoute un argument a la fin du tableau des arguments
void	add_argument(t_command *cmd, char *arg)
{
	char	**new_args;
	int		size;
	int		i;

	if (!arg)
		return ;
	size = ft_strlen_tab(cmd->args);
	new_args = ft_calloc(size + 2, sizeof(char *));
	i = 0;
	while (i < size)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[size] = ft_strdup(arg);
	cmd->args = new_args;
	cmd->argc = size + 1;
}

//on ajoute redir fin tableau des redirs  et on precise le type 
void	add_redirection(t_command *cmd, t_token *token)
{
	t_redir	**new_redir;
	int		size;
	int		i;

	size = 0;
	if (!token)
		return ;
	while (cmd->redir && cmd->redir[size])
		size++;
	new_redir = ft_calloc(size + 2, sizeof(t_redir *));
	i = 0;
	if (cmd->redir)
	{
		while (i < size)
		{
			new_redir[i] = cmd->redir[i];
			i++;
		}
		free(cmd->redir);
	}
	new_redir[size] = malloc(sizeof(t_redir));
	new_redir[size]->file = ft_strdup(token->value);
	new_redir[size]->type = token->type;
	new_redir[size]->append = (token->type == APPEND);
	cmd->redir = new_redir;
}

//on set init parse 
void	init_parse(t_command **cmds, t_command **current)
{
	*cmds = new_command();
	*current = *cmds;
}

// on cree une commande. on parcourt les token. si on rencontre 
// token de type word on lajoute a **args, si redirection a **redir.
// si on rencontre pipe on cree une nouvelle commande et on ajoute au 
// bout de la  liste des commandes. 
// on set builtin value lorsquon pipe et a la fin de la derniere commande. 

t_command	*parse_tokens(t_token **tokens)
{
	t_command	*cmds;
	t_command	*current;
	int			i;

	init_parse(&cmds, &current);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == WORD)
			add_argument(current, tokens[i]->value);
		else if (is_rdir_tok(tokens[i]->type))
			add_redirection(current, tokens[i]);
		else if (tokens[i]->type == PIPE)
		{
			if (current->args && current->args[0])
				current->builtin_value = whichbuiltin(current->args[0]);
			current->next = new_command();
			current = current->next;
		}
		i++;
	}
	if (current->args && current->args[0])
		current->builtin_value = whichbuiltin(current->args[0]);
	return (cmds);
}
