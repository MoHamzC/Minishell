/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:33:59 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 22:56:21 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

int			ft_strlen_tab(char **tab);
t_command	*new_command(void);
void		add_argument(t_command *cmd, char *arg);
void		add_redirection(t_command *cmd, t_token *token);
int			is_rdir_tok(t_cmd_type type);
void		init_parse(t_command **cmds, t_command **current);
t_command	*parse_tokens(t_token **tokens);
int			whichbuiltin(char *s);
void        ft_free_tokens(t_token **tokens); 
void        ft_free_commands(t_command *command); 
void        ft_free_args(char **args);
void        ft_free_redirs(t_redir **redir); 
t_token     *create_token(char *value, t_cmd_type type, t_word_type quote);

#endif // PARSING_H