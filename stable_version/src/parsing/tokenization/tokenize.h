/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:33:59 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/13 20:13:51 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H
# include "minishell.h"

char	*process_complex_token(char *token, t_env *env);
char	*expand_variables_quote(char *str, t_env *env, int quote_type);
void	assign_token_types(t_token **tokens);
void	assign_quote_type(t_token **tokens);
int		finalize_tokens(t_token **tokens, t_env *env);
int		check_pipe_errors(t_token **tokens);
int		check_redirection_errors(t_token **tokens);
int		wich_type(char *token);
char	*expand_variables(char *str, t_env *env);
t_token	**pre_process_redirections(t_token **tokens);

#endif // TOKENIZE_H