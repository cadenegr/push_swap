/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   four_div.c                                         :+:      :+:    :+:   */
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

//where a block [lo, hi) is split: SPLIT_PERCENT of it is the low part that
//goes to the bottom. a bit under 50 means fewer rotations, measured best at 45
int	split_point(int lo, int hi)
{
	return (lo + (hi - lo) * SPLIT_PERCENT / 100);
}

//remembers a block of ranks [lo, hi)
void	add_pile(t_g *g, int lo, int hi)
{
	if (lo >= hi)
		return ;
	g->pile_lo[g->piles] = lo;
	g->pile_hi[g->piles] = hi;
	g->piles++;
}

//keeps the blocks ordered from the smallest ranks to the biggest
void	sort_piles(t_g *g)
{
	int	i;
	int	j;

	i = 0;
	while (++i < g->piles)
	{
		j = i;
		while (j > 0 && g->pile_lo[j - 1] > g->pile_lo[j])
		{
			ft_swap(&g->pile_lo[j - 1], &g->pile_lo[j]);
			ft_swap(&g->pile_hi[j - 1], &g->pile_hi[j]);
			j--;
		}
	}
}

//pushes the top of a to b; a pending rb (low half of the block) goes first
static void	push_and_split(t_g *g, t_s *a, t_s *b, t_v *x)
{
	if (x->turn_on)
		rb(b, g);
	pb(a, b, g);
	x->turn_on = (x->temp < x->j && b->top > 0);
}

//first crossing, a -> b: block by block, every block split in 2 at its own
//split point (low part to the bottom of b). x.k = block end, x.j = split
void	divide_four(t_g *g, t_s *a, t_s *b, int blocks)
{
	t_v	x;

	x.i = 0;
	x.turn_on = false;
	g->piles = 0;
	while (++x.i <= blocks)
	{
		x.k = g->size * x.i / blocks;
		x.j = split_point(g->size * (x.i - 1) / blocks, x.k);
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
		add_pile(g, g->size * (x.i - 1) / blocks, x.j);
		add_pile(g, x.j, x.k);
	}
	if (x.turn_on)
		rb(b, g);
	sort_piles(g);
}
