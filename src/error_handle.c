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

//checks the arg: numbers split by spaces, each one an optional + or -
//and 1 to 12 digits. an arg with no number at all is wrong too.
bool	correct_arguments(char *argv)
{
	t_v	x;

	x.i = 0;
	x.count = 0;
	while (argv[x.i])
	{
		while (argv[x.i] == ' ')
			x.i++;
		if (!argv[x.i])
			break ;
		if (argv[x.i] == '-' || argv[x.i] == '+')
			x.i++;
		x.length = 0;
		while (ft_isdigit(argv[x.i]) && ++x.length)
			x.i++;
		if (x.length == 0 || x.length > 12 || (argv[x.i] && argv[x.i] != ' '))
			return (false);
		x.count++;
	}
	return (x.count > 0);
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
