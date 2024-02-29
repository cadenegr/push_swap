/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:45:01 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/16 11:22:27 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last = i;
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	if (last != -1)
		return ((char *)&s[last]);
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	char *str = "Hello my little friend!";
	char *ptr;

	ptr = ft_strrchr(str, 'f');
	printf("ptr: %s\n", ptr);
	return (0);
}*/
