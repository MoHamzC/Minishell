/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:36:14 by calberti          #+#    #+#             */
/*   Updated: 2025/02/13 18:13:50 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}
/*
#include <fcntl.h>
int	main(int argc, char **argv)
{
    int fd = open ("test.txt", O_WRONLY | O_CREAT, 0644);
	if (argc == 2)
	{
		ft_putstr_fd(argv[1], fd);
	}
	return (0);
}
//0644 lire/ecrire par le proprio et lire pour les autres
//0 entre standard
//1 sortie standard
//2 sortie d'erreur
//3, 4, 5... les fichier qui seront succesivement ouvert
*/
