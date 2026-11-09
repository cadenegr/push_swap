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
	g->size = 0;
	if (more_arguments(argc, argv, g) == 0)
		return (0);
	if (!parameters(g))
		return (0);
	low_high_values(g);
	ft_qsort(g->sorted_array, 0, g->size - 1);
	return (1);
}

//reads every number of one argument: "5" or "5 3 8" (spaces at the ends ok)
void	two_arguments(char *argv, t_g *g)
{
	t_v	x;

	x.i = 0;
	x.k = ft_strlen(argv);
	while (x.i < x.k)
	{
		while (argv[x.i] == ' ')
			x.i++;
		if (!argv[x.i])
			break ;
		if (g->size >= MAX_SIZE)
		{
			g->size = -1;
			return ;
		}
		g->long_array[g->size] = ft_atol_index(argv, &x.i);
		g->original_array[g->size] = g->long_array[g->size];
		g->sorted_array[g->size] = g->long_array[g->size];
		g->size++;
	}
}

//checks and reads every argument; returns 0 on a wrong one or too many numbers
int	more_arguments(int argc, char **argv, t_g *g)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!correct_arguments(argv[i]))
			return (0);
		two_arguments(argv[i], g);
		if (g->size < 0)
			return (0);
		i++;
	}
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
