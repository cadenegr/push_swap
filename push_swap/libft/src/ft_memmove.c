/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:29:22 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/27 20:06:03 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ifptrsrclessptrdest(char *ptr_dest, const char *ptr_src, size_t n)
{
	while (n > 0)
	{
		ptr_dest[n - 1] = ptr_src[n - 1];
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*ptr_dest;
	const char	*ptr_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	ptr_dest = dest;
	ptr_src = src;
	if (ptr_src < ptr_dest)
	{
		ifptrsrclessptrdest(ptr_dest, ptr_src, n);
	}
	else
	{
		while (i < n)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main()
{
	char src[] = "Hello!";
	char dest[100];

	ft_memmove(dest, src, 5);

	printf("src: %s\n", src);
	printf("dest: %s\n", dest);

	return (0);
}*/
