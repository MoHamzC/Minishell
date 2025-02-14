/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:33:59 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/14 08:12:34 by mochamsa         ###   ########.fr       */
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
int		is_redir_char(char *c);
int		three_redir(char *line);
char	*add_spaces_around_specials(char *input);
int		skip_quotes_syntax(const char *str);
void 	skip_quotes(const char *str, char **res, size_t *i, size_t *j);
void	show_tokens(t_token **tokens);
int 	check_quotes(const char *str);

#endif // TOKENIZE_H