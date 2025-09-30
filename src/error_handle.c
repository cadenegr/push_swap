/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:08:11 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/14 14:14:30 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//checks if the arg, is digit, space, minus or plus.
bool	correct_arguments(char *argv)
{
	t_v	x;

	x.i = 0;
	while (argv[x.i])
	{
		if (ft_isdigit(argv[x.i]) || argv[x.i] == ' ')
			x.i++;
		else if ((argv[x.i] == '-' || argv[x.i] == '+')
			&& (x.i == 0 || argv[x.i - 1] == ' '))
			x.i++;
		else
			return (false);
	}
	return (true);
}

//reception to send arg.
bool	parameters(t_g *g)
{
	if (!int_size(g))
		return (0);
	if (!duplicate(g))
		return (0);
	return (1);
}

//checks if the arg is within the INT size
bool	int_size(t_g *g)
{
	int	i;

	i = 0;
	while (i < g->size)
	{
		if (g-> long_array[i] <= 2147483647
			&& g->long_array[i] >= -2147483648)
			i++;
		else
			return (0);
	}
	return (1);
}

//loops to check if there are any duplicates num in the stack
bool	duplicate(t_g *g)
{
	t_v		x;
	int		array_size;

	x.i = 0;
	x.j = 0;
	array_size = g->size;
	while (x.i < array_size)
	{
		x.temp = g->long_array[x.i];
		if (x.temp == g->long_array[x.j]
			&& x.i != x.j)
			return (0);
		else if (x.j == array_size - 1)
		{
			x.i++;
			x.j = 0;
		}
		else
			x.j++;
	}
	x.temp = 0;
	return (1);
}
