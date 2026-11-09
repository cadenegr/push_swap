/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_eight_div.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:39:13 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 18:06:21 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//the three moves of a crossing, for both directions
//to_a: b -> a (rrb, pa, ra)    otherwise: a -> b (rra, pb, rb)
static void	cross_move(t_g *g, t_s *a, t_s *b, int move)
{
	if (move == 0 && g->to_a)
		rrb(b, g);
	else if (move == 0)
		rra(a, g);
	else if (move == 1 && g->to_a)
		pa(b, a, g);
	else if (move == 1)
		pb(a, b, g);
	else if (move == 2 && g->to_a)
		ra(a, g);
	else if (move == 2)
		rb(b, g);
}

//moves the block [lo, hi) to the other stack. it is either on top of the
//source or at its bottom (then each number needs a reverse rotate first).
//its low half goes to the bottom of the destination: the block splits in 2
static void	move_pile(t_g *g, t_s *a, t_s *b, t_v *x)
{
	t_s	*src;
	t_s	*dst;

	src = a;
	dst = b;
	if (g->to_a)
	{
		src = b;
		dst = a;
	}
	x->count = x->k - x->i;
	while (x->count-- > 0)
	{
		x->temp = search(src->s, src->top, g);
		if (x->temp < x->i || x->temp >= x->k)
			cross_move(g, a, b, 0);
		x->temp = search(src->s, src->top, g);
		cross_move(g, a, b, 1);
		if (x->temp < x->j && dst->top > 0)
			cross_move(g, a, b, 2);
	}
}

//one crossing: every block goes to the other stack, biggest block first
//when going to a, smallest first when going to b, and every block is split
//in 2 on the way. so the blocks double: 8 -> 16 -> 32 ...
void	divide_eight(t_g *g, t_s *a, t_s *b, bool to_a)
{
	t_v	x;
	int	lo[MAX_SIZE];
	int	hi[MAX_SIZE];
	int	n;
	int	i;

	n = g->piles;
	i = -1;
	while (++i < n)
	{
		lo[i] = g->pile_lo[i];
		hi[i] = g->pile_hi[i];
	}
	g->to_a = to_a;
	g->piles = 0;
	i = -1;
	while (++i < n)
	{
		x.i = lo[i * !to_a + (n - 1 - i) * to_a];
		x.k = hi[i * !to_a + (n - 1 - i) * to_a];
		x.j = split_point(x.i, x.k);
		move_pile(g, a, b, &x);
		add_pile(g, x.i, x.j);
		add_pile(g, x.j, x.k);
	}
	sort_piles(g);
}
