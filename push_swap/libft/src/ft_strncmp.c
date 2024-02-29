/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:35:23 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/27 17:22:21 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char	first[] = "Hello";
	char	second[] = "Heyya";

	printf ("%d", strncmp(first, second, 2));
	printf ("\n%d", ft_strncmp(first, second, 2));

    char    first1[] = "Helloa";
    char    second1[] = "Helloz";

    printf("\n%d", strncmp(first1, second1, 6));
    printf("\n%d", ft_strncmp(first1, second1, 6));
	return(0);
}*/
