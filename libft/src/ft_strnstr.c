/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:39:47 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/16 13:06:54 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*big_ptr;
	const char	*little_ptr;
	size_t		i;

	big_ptr = big;
	little_ptr = little;
	i = 0;
	if (little_ptr[0] == '\0')
		return ((char *)big_ptr);
	while (big_ptr[i] != '\0' && i < len)
	{
		if (big_ptr[i] == little_ptr[0])
		{
			if (ft_memcmp(&big_ptr[i], little_ptr, ft_strlen(little_ptr)) == 0)
			{
				if (i + ft_strlen(little_ptr) <= len)
					return ((char *)&big_ptr[i]);
			}
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	char *str1 = "Hello my little friend!";
	char *str2 = "y";
	int n = 15;

	printf("strnstr: %s\n", strnstr(str1, str2, n));
	printf("ft_strnstr: %s\n", ft_strnstr(str1, str2, n));

	char *result = ft_strnstr(str1, str2, n);
if (result != NULL)
    printf("ft_strnstr: %s\n", result);
else
    printf("ft_strnstr: Substring not found\n");

	return (0);
}
*/
