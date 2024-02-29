/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:14:39 by cadenegr          #+#    #+#             */
/*   Updated: 2023/06/27 19:55:41 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0 && base == 10)
		len++;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*ptr;
	const char	*base = "0123456789";

	len = ft_numlen(n, 10);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[len] = 0;
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
		ptr[0] = '-';
	while (n != 0)
	{
		if (n > 0)
			ptr[--len] = base[n % 10];
		else
			ptr[--len] = base[-(n % 10)];
		n /= 10;
	}
	return (ptr);
}

/*
#include <stdio.h>
int	main()
{
	char *str;

	str = ft_itoa(-2147483648);
	printf("%s\n", str);
	return (0);
}
*/
