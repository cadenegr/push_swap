/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:08:27 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/14 14:45:35 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//initializes the top of the stacks to -1, builds stack a
void	init_stacks(t_g *g, t_s *a, t_s *b)
{
	initialize_stack(&a->top);
	initialize_stack(&b->top);
	build_a_stack(g, a);
}

//stack a build, by pushing it from the array
void	build_a_stack(t_g *g, t_s *a)
{
	t_v	x;

	x.i = 0;
	x.j = g->size - 1;
	while (x.i < g->size)
	{
		push(a->s, &a->top, g->original_array[x.j]);
		x.i++;
		x.j--;
	}
}
