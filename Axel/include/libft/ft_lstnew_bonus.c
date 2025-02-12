/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 08:27:27 by axburin-          #+#    #+#             */
/*   Updated: 2024/10/23 17:26:43 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*s_list;

	s_list = malloc(sizeof(t_list));
	if (!s_list)
		return (NULL);
	s_list->content = content;
	s_list->next = NULL;
	return (s_list);
}
