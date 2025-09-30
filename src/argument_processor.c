/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:43:47 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 17:19:23 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//reception for the argument to be process
int	argument_processor(int argc, char **argv, t_g *g)
{
	if (argc < 2)
		return (0);
	if (!correct_arguments(argv[1]))
		return (0);
	if (argc == 2)
		two_arguments(argv[1], g);
	if (argc > 2)
	{
		if (more_arguments(argc, argv, g) == 0)
			return (0);
	}
	if (!g->original_array)
		return (0);
	if (!parameters(g))
		return (0);
	low_high_values(g);
	ft_qsort(g->sorted_array, 0, g->size - 1);
	return (1);
}

//if the argument is within "quotations" 
void	two_arguments(char *argv, t_g *g)
{
	t_v	x;

	x.i = 0;
	x.j = 0;
	x.k = ft_strlen(argv);
	while (x.i < x.k)
	{
		g->long_array[x.j] = ft_atol_index(argv, &x.i);
		g->original_array[x.j] = g->long_array[x.j];
		g->sorted_array[x.j] = g->long_array[x.j];
		x.j++;
	}
	g->size = x.j;
}

//if the arguments are individually input
int	more_arguments(int argc, char **argv, t_g *g)
{
	t_v	x;

	x.i = 0;
	x.j = 1;
	while (argc > x.j)
	{
		if (!correct_arguments(argv[x.j]))
			return (0);
		else
		{
			g->long_array[x.i] = ft_atol(argv[x.j]);
			g->original_array[x.i] = g->long_array[x.i];
			g->sorted_array[x.i] = g->long_array[x.i];
			x.i++;
		}
		x.j++;
	}
	g->size = argc - 1;
	return (1);
}

//finds the smallest and biggest numbers of the stack.
void	low_high_values(t_g *g)
{
	int	i;
	int	array_size;

	i = 0;
	g->low = g->long_array[i];
	g->high = g->long_array[i];
	array_size = g->size;
	while (i < array_size)
	{
		if (g->low > g->long_array[i])
			g->low = g->long_array[i];
		if (g->high < g->long_array[i])
			g->high = g->long_array[i];
		i++;
	}
}
