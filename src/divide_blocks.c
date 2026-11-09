/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_blocks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:21:43 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 18:02:44 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//rank of the top of a stack: its index in the sorted array
int	search(int *array, int top, t_g *g)
{
	int	i;

	i = 0;
	while (i < g->size)
	{
		if (array[top] == g->sorted_array[i])
			break ;
		i++;
	}
	return (i);
}

//blocks = about 0.4 * sqrt(size): 100 -> 4 blocks, 500 -> 9 blocks.
//measured: more blocks cost more ra, fewer blocks cost more rb later.
int	how_many_blocks(int size)
{
	int	blocks;

	blocks = 1;
	while (blocks * blocks * 25 < size * 4)
		blocks++;
	return (blocks);
}

//pushes the top of a to b; a pending rb (low half of the block) is done first
static void	push_and_split(t_g *g, t_s *a, t_s *b, t_v *x)
{
	if (x->turn_on)
		rb(b, g);
	pb(a, b, g);
	x->turn_on = (x->temp < x->j && b->top > 0);
}

//sends a to b block by block. every block is split in 2 inside b:
//its low half goes to the bottom of b, its high half stays on top.
//an rb followed by an ra is merged into one rr.
//x.k = end of the block (rank), x.j = middle of the block (rank)
void	divide_blocks(t_g *g, t_s *a, t_s *b, int blocks)
{
	t_v	x;

	x.i = 0;
	x.turn_on = false;
	while (++x.i <= blocks)
	{
		x.k = g->size * x.i / blocks;
		x.j = (g->size * (x.i - 1) / blocks + x.k) / 2;
		while (b->top + 1 < x.k)
		{
			x.temp = search(a->s, a->top, g);
			if (x.temp < x.k)
				push_and_split(g, a, b, &x);
			else if (x.turn_on)
			{
				rr(a, b, g);
				x.turn_on = false;
			}
			else
				ra(a, g);
		}
	}
	if (x.turn_on)
		rb(b, g);
}
