/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:06:24 by calberti          #+#    #+#             */
/*   Updated: 2025/02/13 19:45:48 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

//size_t			ft_strlen(char *str);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*get_line_from_buffer(char **buffer);
char		*get_next_line(int fd);
char		*ft_strchr_gnl(const char *s, int c);

#endif
