/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:46:58 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/23 12:49:35 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	aux;

	aux = n;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (aux < 0)
	{
		write(fd, "-", 1);
		aux = aux * -1;
	}
	if (aux > 9)
	{
		ft_putnbr_fd(aux / 10, fd);
		ft_putnbr_fd(aux % 10, fd);
	}
	else
	{
		aux = aux + '0';
		write(fd, &aux, 1);
	}
}
/*
int	main()
{
	ft_putnbr_fd(-2147483648, 1);
	return (0);
}*/
