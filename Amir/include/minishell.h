/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:58 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/12 05:52:15 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include <stdbool.h>

typedef enum e_builtin
{
	NOT_BUILTIN = -1,
	ECHO = 0,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,	
}				t_builtin;

typedef enum token_type
{
	WORD,
	REDIRIN,
	REDIROUT,
	APPEND,
	HERE_DOC,	
	PIPE,
}	t_cmd_type;

typedef enum word_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_word_type;

typedef struct s_token
{
	char		*value;
	t_cmd_type	type;
	t_word_type	quote;
}	t_token;

typedef struct s_redir
{
	char	*file;
	int		type;
	bool	append;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_command
{
	t_redir				**redir;
	char				**args;
	int					builtin_value;
	struct s_command	*next;
}				t_command;

typedef struct s_shell
{
	t_command	*cmds;
	t_env		*env;
}	t_shell;

int		ft_isspace(char c);
t_token	**tokenize(char *line);
int		post_tokenize(t_token **tokens, t_env *env);
void	free_tokens(t_token **tokens);

t_env	*ft_envlst_new(char *key, char *value);
void	ft_envlst_add_back(t_env **lst, t_env *new);
t_env	*init_env(char **envp);
void	free_env(t_env *env);
t_token	**pre_process_redirections(t_token **tokens);
t_token	**take_ur_token_and_leave_me_alone(t_env *env, char *line);
#endif
