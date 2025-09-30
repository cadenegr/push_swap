/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:47:07 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/16 11:39:24 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	i = 0;
	if (size <= dest_len)
		return (src_len + size);
	while (src[i] != '\0' && (dest_len + i) < (size - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}

/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char dest[] = "Hello";
	char src[] = "world!";
	unsigned int size = sizeof(dest);

	unsigned int res = ft_strlcat (dest, src, size);

	printf ("Concatenated string: %s\n", dest);
	printf ("Total length: %u\n", res);
	printf ("Expected length: %lu\n", strlen("Hello world!"));
	return (0);
}*/
