/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:11:32 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/02 11:26:45 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol_index(const char *s, int *counter)
{
	int		i;
	int		neg;
	long	num;

	i = *counter;
	neg = 0;
	num = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '\0')
		num = 2147483648;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			neg++;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		num = num * 10 + (s[i++] - '0');
	if (neg == 1)
		num *= -1;
	*counter = i;
	return (num);
}
/*
// #include	<stdio.h>
// int	main(void)
// {
// 	int	counter;

// 	counter = 0;
// 	printf("%ld\n", ft_atol_index("-51234565456565", &counter));
// 	return(0);
// }*/
