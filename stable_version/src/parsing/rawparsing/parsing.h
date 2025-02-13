/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:33:59 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 02:42:35 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

int ft_strlen_tab(char **tab);
t_command *new_command(void); 
void	add_argument(t_command *cmd, char *arg); 
void	add_redirection(t_command *cmd, t_token *token); 
int	is_rdir_tok(t_cmd_type type);
void init_parse(t_command **cmds, t_command **current); 
t_command	*parse_tokens(t_token **tokens); 
int whichbuiltin(char *s);

#endif // PARSING_H