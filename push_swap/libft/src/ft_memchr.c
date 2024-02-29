/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:11:53 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/27 17:25:40 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	chr;

	ptr = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n--)
	{
		if (*ptr == chr)
			return (ptr);
		ptr++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	char *str = "Hello my little friend!";
	char *ptr;

	ptr = memchr(str, 'l', 5);
	printf("ptr: %s\n", ptr);
	return (0);
}*/
